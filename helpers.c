#include <math.h>
#include <stdio.h>

#include "rtree.h"

Rect createMBR(Rect rect1,
               Rect rect2)  // this is a function to create an area of samllest area that encloses rect1 and rect2
{
    Rect rect;
    rect.topRight.x =
        fmax(rect1.topRight.x,
             rect2.topRight.x);  // these 4 similar looking statements basically find the bottomleft and topright
    rect.topRight.y =
        fmax(rect1.topRight.y,
             rect2.topRight.y);  // coordinates of the enclosing rectangle among two rectangles that bound them.
    rect.bottomLeft.x =
        fmin(rect1.bottomLeft.x,
             rect2.bottomLeft.x);  // Refer to diagram in slides to understand the logic if you are still unclear
    rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);

    return rect;
}

int calculateAreaOfRectangle(Rect rect)  // Returns the area of the rectangle
{
    int height = abs(rect.topRight.x - rect.bottomLeft.x);  // we are considering only horizontal and vertical
                                                            // rectangles hence computation of area is straighforward
    int width = abs(rect.topRight.y - rect.bottomLeft.y);
    return height * width;  // returns the area(length*breadth)
}

int calcAreaEnlargement(Rect rectCont, Rect rectChild)  // this is function is used to calculate the amount of area an
                                                        // MBR must expand by inorder to enclose the new added MBR
{
    Rect enlargedRect = createMBR(rectCont, rectChild);  // new enlarged rectangle created

    return calculateAreaOfRectangle(enlargedRect) -
           calculateAreaOfRectangle(rectCont);  // this returns the minimum amount of
    // area an MBR(rectCont) must expand by inorder to enclose the new added MBR(rectChild)
}

void createNodeParent(Node *node)  // lets say we might have created a node somewhere to
{  // handle certain logic where we have to deal with its parent we are creating a node_ele parent whose child will
   // point to the current node
    if (node->parent != NULL)
    {
        free(node->parent);  // doing this just incase the node's parent is pointing to some random place
    }
    Rect mbr;
    mbr = node->elements[0]->mbr;  // initialising mbr to the first node_ele of the node passed as function parameters
    for (int i = 1; i < node->count; i++)  // max 4 node_ele are allowed hence i goes from 0 to 3
    {
        mbr = createMBR(mbr, node->elements[i]->mbr);  // this statement if you observer closely creates the rectangle
                                                       // that bounds all the node->elements[i]->mbr
    }  // or in otherwords creates the parent MBR structure from where are current node descended from
    Node_ele *parent = createNodeEle(
        NULL, mbr.topRight, mbr.bottomLeft);  // Now the big mbr created in the previous step is encapsulated within the
                                              // struct node_ele hence we are creating the container for this mbr
    node->parent = parent;  // finally making the node->parent point to its correct parent
    parent->child = node;   // and handling the parent's child to also correct point to our current node
    parent->mbr = mbr;      // and finally to handle all attributes of our struct node_ele parent we are assigning it to
                        // have the big mbr which we created
}

void updateParent(Node_ele *parent, Node *node1,
                  Node *node2)  // this is the method which handles struct splitResult's attributes
{  // now look at the function parameters: so according to the struct splitResult leaf1 is node1,leaf2 is node2 and the
   // node_ele parent of struct splitResult is labelled as parent itself
    Node *parentNode = parent->container;  // creating a placeholder for the node which will now contain the node_ele
                                           // parent of the function parameters
    int ele;  // this varaiable ele is being used as an index
    for (int i = 0; i < parentNode->count; i++)
    {
        if (parentNode->elements[i] ==
            parent)  // this loop is used to allot the appropriate index to ele at which are node_ele parent is present
                     // within the array present in the struct node parentNode
        {
            ele = i;  // this simply to find the index and assign it to a variable as explained above
            break;
        }
    }
    parentNode->elements[ele] =
        node1->parent;  // now this parentNode's node_ele is made the parent of node1 which didn't exist before because
                        // it was present inside the temporary struct splitResult
    node1->parent->container = parentNode;  // similarly we assign the appropriate pointers present in node to point
                                            // correctly to its parent node
    if (node1 !=
        node2)  // the if satement is designed like this because in somecases node1 might equal to node2, especially
                // when its not splitting, this point is explained properly where this case is being used
    {
        parentNode->elements[parentNode->count++] =
            node2->parent;  // handling the pointers in the same way that we handled it for node1 in the exact same way
        node2->parent->container = parentNode;
    }
    free(parent);  // as mentioned previously splitResult is a temporary struct created to handle the splitting of a
                   // node so we are freeing one of its attribtues, the other attributes are handled appropriately in
                   // the other parts of the code
}
