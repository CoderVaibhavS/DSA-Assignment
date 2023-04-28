#include <math.h>
#include <stdio.h>
<<<<<<< Updated upstream

=======
#include <stdlib.h>
#include <stdbool.h>
>>>>>>> Stashed changes
#include "rtree.h"

int calcAreaEnlargement(Rect rectCont, Rect rectChild)
{
    int xMin = fmin(rectCont.bottomLeft.x, rectChild.bottomLeft.x);
    int yMin = fmin(rectCont.bottomLeft.y, rectChild.bottomLeft.y);
    int xMax = fmax(rectCont.topRight.x, rectChild.topRight.x);
    int yMax = fmax(rectCont.topRight.y, rectChild.topRight.y);

    Rect enlargedRect;
    enlargedRect.topRight.x = xMax;
    enlargedRect.topRight.y = yMax;
    enlargedRect.bottomLeft.x = xMin;
    enlargedRect.bottomLeft.y = yMin;

    return calculateAreaOfRectangle(enlargedRect) - calculateAreaOfRectangle(rectCont);
}

Node_ele* chooseSubTree(Node* node, Rect rectAdd)
{
<<<<<<< Updated upstream
    int ele = 0;
    int areaMin = calculateAreaOfRectangle(node->elements[0]->mbr);
    int areaEnlarge = calcAreaEnlargement(node->elements[0]->mbr, rectAdd);

    for (int i = 1; i < node->count; i++)
    {
        if (node->elements[i] != NULL)
        {
            int areaE = calcAreaEnlargement(node->elements[i]->mbr, rectAdd);
            int area = calculateAreaOfRectangle(node->elements[i]->mbr);
            if (areaE < areaEnlarge)
            {
                areaMin = area;
                areaEnlarge = areaE;
                ele = i;
            }
            else if (areaE == areaEnlarge)
            {
                if (area < areaMin)
                {
                    areaMin = area;
                    areaEnlarge = areaE;
                    ele = i;
                }
            }
        }
        else
=======
    int area1 = calculateAreaOfRectangle(n->elements[0]->mbr);
    int area2 = calculateAreaOfRectangle(n->elements[1]->mbr);
    int area3 = calculateAreaOfRectangle(n->elements[2]->mbr);
    int area4 = calculateAreaOfRectangle(n->elements[3]->mbr);
    Node* child = NULL;

    // finding the rectangle with the minimum area
    int min_area = calculateAreaOfRectangle(
        n->elements[0]->mbr);  // Assume the first area is the minimum
    int area;

    area = calculateAreaOfRectangle(n->elements[1]->mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    area = calculateAreaOfRectangle(n->elements[2]->mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    area = calculateAreaOfRectangle(n->elements[3]->mbr);
    if (area < min_area)
    {
        min_area = area;
    }

    for (int i = 0; i < 4; i++)
    {
        if (calculateAreaOfRectangle(n->elements[i]->mbr) == area)
        {
            return n->elements[i]->child;
        }
    }
    return child;  // code will logically never reach this return statement
                   // because of the logic mentioned above...its a line just to
                   // prevent syntax/compile time error because a function must
                   // terminate with a return statement

    // this else part is not handled properly
}

// int LeafCheck(Node* n)
// {
//     if (n.children[0] == NULL && n.children[1] == NULL && n.children[2] ==
//     NULL && n.children[3] == NULL)
//     {
//         return 1;
//     }
//     else
//         return 0;
// }

Node* descendTree(Node* n)
{
    bool status1 = n->elements[0]->child->is_leaf;
    bool status2 = n->elements[1]->child->is_leaf;
    bool status3 = n->elements[2]->child->is_leaf;
    bool status4 = n->elements[3]->child->is_leaf;

    if (status1 == 1)
    {
        return n->elements[0]->child;
    }
    else if (status2 == 1)
    {
        return n->elements[1]->child;
    }
    else if (status3 == 1)
    {
        return n->elements[2]->child;
    }
    else if (status4 == 1)
    {
        return n->elements[3]->child;
    }
    else
    {  // else to recrusively check if its leaf node and if its not descend down
       // the tree
        Node* result = NULL;
        result = descendTree(n->elements[0]->child);
        if (result != NULL)
>>>>>>> Stashed changes
        {
            break;
        }
<<<<<<< Updated upstream
=======

        result = descendTree(n->elements[1]->child);
        if (result != NULL)
        {
            return result;
        }

        result = descendTree(n->elements[2]->child);
        if (result != NULL)
        {
            return result;
        }

        result = descendTree(n->elements[3]->child);
        return result;
>>>>>>> Stashed changes
    }

    return node->elements[ele];
}

Node* ChooseLeaf(Rtree* tree, Rect rectAdd)
{
    Node* node = tree->root;
    while (!node->is_leaf)
    {
        node = chooseSubTree(node, rectAdd)->child;
    }
    Rect mbr = node->parent->mbr;
    printf("(%d, %d) -> (%d, %d)", mbr.bottomLeft.x, mbr.bottomLeft.y, mbr.topRight.x, mbr.topRight.y);
    return node;
}
