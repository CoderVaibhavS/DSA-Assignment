#include <math.h>
#include <stdio.h>
#include "rtree.h"

// choose the appropriate subtree where new rectangle can be added
Node_ele* chooseSubTree(Node* node, Rect rectAdd)
{
    int ele = 0;    // to keep track of the index
    int areaMin = calculateAreaOfRectangle(node->elements[0]->mbr);     // to store min area of rectangles
    int areaEnlarge = calcAreaEnlargement(node->elements[0]->mbr, rectAdd);     // enlarged area

    for (int i = 1; i < node->count; i++)       // iterate over node_ele other than 1st one
    {
        if (node->elements[i] != NULL)
        {
            int area = calculateAreaOfRectangle(node->elements[i]->mbr);
            int areaE = calcAreaEnlargement(node->elements[i]->mbr, rectAdd);

            if (areaE < areaEnlarge)  // min area enlargement
            {
                areaMin = area;
                areaEnlarge = areaE;
                ele = i;
            }
            else if (areaE == areaEnlarge) 
            {
                if (area < areaMin)     // allot rectangle having the smaller area
                {
                    areaMin = area;
                    areaEnlarge = areaE;
                    ele = i;
                }
            }
        }
        else 
        {
            break;
        }
    }

    return node->elements[ele];  // subtree where rectangle is to be added
}

Node* ChooseLeaf(Rtree* tree, Rect rectAdd) 
{
    Node* node = tree->root;
    while (!node->is_leaf)    // running loop until leaf is reached
    {
        node = chooseSubTree(node, rectAdd)->child;  // descends down to the leaf node
    }

    return node;  // correct leaf node
}
