#include "rtree.h"
#include <stdio.h>
#include <stdlib.h>

// Before creating the search algorithm we will first create the methods required for insertion
// Choosing which Node to insert new elemnt to function as per research paper
int CalculateAreaOfMBR(Rect rect)
{
    int length = abs(rect.topRight.x - rect.bottomLeft.x); // this is length of rectangle
    int width = abs(rect.topRight.y - rect.bottomLeft.y);  // this is width of rectangle
    int area = (length * width);
    return area;
}

Node* chooseSubTree(Node* n) // read
{

    int area1 = CalculateAreaOfMBR(n->elements[0].mbr);
    int area2 = CalculateAreaOfMBR(n->elements[1].mbr);
    int area3 = CalculateAreaOfMBR(n->elements[2].mbr);
    int area4 = CalculateAreaOfMBR(n->elements[3].mbr);
    Node* child=NULL;

    // finding the rectangle with the minimum area
    int min_area = CalculateAreaOfMBR(n->elements[0].mbr); // Assume the first area is the minimum
    int area;

    area = CalculateAreaOfMBR(n->elements[1].mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    area = CalculateAreaOfMBR(n->elements[2].mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    area = CalculateAreaOfMBR(n->elements[3].mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if(CalculateAreaOfMBR(n->elements[i].mbr) == area)
        {
            return n->elements[i].child;

         }
    }
    return child; //code will logically never reach this return statement because of the logic mentioned above...its a line just to prevent syntax/compile time error because a function must terminate with a return statement
        
    // this else part is not handled properly
}

// int LeafCheck(Node* n)
// {
//     if (n.children[0] == NULL && n.children[1] == NULL && n.children[2] == NULL && n.children[3] == NULL)
//     {
//         return 1;
//     }
//     else
//         return 0;
// }

Node* descendTree(Node* n)
{
    bool status1 = n->elements[0].child->is_leaf;
    bool status2 = n->elements[1].child->is_leaf;
    bool status3 = n->elements[2].child->is_leaf;
    bool status4 = n->elements[3].child->is_leaf;

    if (status1 == 1)
    {
        return n->elements[0].child;
    }
    else if (status2 == 1)
    {
        return n->elements[1].child;
    }
    else if (status3 == 1)
    {
        return n->elements[2].child;
    }
    else if (status4 == 1)
    {
        return n->elements[3].child;
    }
    else
    { // else to recrusively check if its leaf node and if its not descend down the tree
        Node* result = NULL;
        result = descendTree(n->elements[0].child);
        if (result != NULL)
        {
            return result;
        }

        result = descendTree(n->elements[1].child);
        if (result != NULL)
        {
            return result;
        }

        result = descendTree(n->elements[2].child);
        if (result != NULL)
        {
            return result;
        }

        result = descendTree(n->elements[3].child);
        return result;
    }
}

// NOTE while implementing ChooseLeaf in the main function we will feed it the root node of the tree
Rect ChooseLeaf(Node* n) // this method is still incomplete, I am yet to finish this
{
    // Start at root node
    bool status = n->is_leaf;
    if (status == 1)
    {
        return n->elements[0].mbr;
    }
    else
    {

        ChooseLeaf(descendTree(chooseSubTree(n)));// recursively calling ChooseLeaf to call CL2,CL3 and CL4
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------