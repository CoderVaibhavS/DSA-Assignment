#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "rtree.h"

Rect createMBR(Rect rect1,
               Rect rect2)  // this is a function to create an area of samllest area that encloses rect1 and rect2
{
    Rect rect;
    // these 4 similar looking statements basically find the bottomleft and topright
    rect.topRight.x = fmax(rect1.topRight.x, rect2.topRight.x);
    // coordinates of the enclosing rectangle among two rectangles that bound them.
    rect.topRight.y = fmax(rect1.topRight.y, rect2.topRight.y);
    // Refer to diagram in slides to understand the logic if you are still unclear
    rect.bottomLeft.x = fmin(rect1.bottomLeft.x, rect2.bottomLeft.x);
    rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);

    return rect;
}

int calculateAreaOfRectangle(Rect rect)  // Returns the area of the rectangle
{
    // Consider only horizontal and vertical rectangles
    int height = abs(rect.topRight.x - rect.bottomLeft.x);
    int width = abs(rect.topRight.y - rect.bottomLeft.y);
    return height * width;  // returns the area(length*breadth)
}

// Calculate the area by which rectCont has to expand to accomodate rectChild
int calcAreaEnlargement(Rect rectCont, Rect rectChild)
{
    Rect enlargedRect = createMBR(rectCont, rectChild);  // new enlarged rectangle created

    return calculateAreaOfRectangle(enlargedRect) -
           calculateAreaOfRectangle(rectCont);  // this returns the minimum amount of
    // area an MBR(rectCont) must expand by inorder to enclose the new added MBR(rectChild)
}

// Create a parent Node_ele(MBR) for node.
void createNodeParent(Node *node)
{
    Rect mbr;
    Node_ele *oldParent = node->parent;
    // MBR of 0th node is 0th node itelf
    mbr = node->elements[0]->mbr;
    // Calculate the parent's MBR by repeatedly checking max and min value of container of previous MBRs and current MBR
    for (int i = 1; i < node->count; i++)
    {
        mbr = createMBR(mbr, node->elements[i]->mbr);

    }  // or in otherwords creates the parent MBR structure from where are current node descended from
    Node_ele *parent = createNodeEle(NULL, mbr.topRight, mbr.bottomLeft);
    // Assign the appopriate fields
    node->parent = parent;
    parent->child = node;
    parent->mbr = mbr;
    if (oldParent != NULL)
    {
        node->parent->container = oldParent->container;
        free(oldParent);
    }
}

// Update `node1` and `node2` parent MBRs in container of `parent` MBR
void updateParent(Node_ele *parent, Node *node1, Node *node2)
{
    // creating a placeholder for the node which will now contain the node_ele
    // parent of the function parameters
    Node *parentNode = parent->container;
    // this varaiable ele is being used as an index
    int ele;
    // Find the index at which `parent` MBR is present
    for (int i = 0; i < parentNode->count; i++)
    {
        if (parentNode->elements[i] == parent)
        {
            ele = i;
            break;
        }
    }
    // now this parentNode's node_ele is made the parent of node1 which didn't exist before because
    // it was present inside the temporary struct splitResult
    parentNode->elements[ele] = node1->parent;
    node1->parent->container = parentNode;
    // similarly we assign the appropriate pointers present in node to point
    // correctly to its parent node
    if (node1 != node2)
    // the if satement is designed like this because in somecases node1 might equal to node2, especially
    // when its not splitting, this point is explained properly where this case is being used
    {
        parentNode->elements[parentNode->count++] =
            node2->parent;  // handling the pointers in the same way that we handled it for node1 in the exact same way
        node2->parent->container = parentNode;
    }
    // Free the old parent since it is no longer required
    if (node1 != node2) free(parent);
}
