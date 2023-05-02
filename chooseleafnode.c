#include <math.h>
#include <stdio.h>

#include "rtree.h"

// choose the appropriate subtree where new rectangle can be added
NodeEle* chooseSubTree(Node* node, Rect rectAdd)
{
    // Init variables
    int ele = 0;
    int areaMin = calculateAreaOfRectangle(node->elements[0]->mbr);          // to store min area of rectangles
    int areaEnlarge = calcAreaEnlargement(node->elements[0]->mbr, rectAdd);  // enlarged area

    // Check for maximum enlargement
    for (int i = 1; i < node->count; i++)
    {
        if (node->elements[i] != NULL)
        {
            int area = calculateAreaOfRectangle(node->elements[i]->mbr);
            int areaE = calcAreaEnlargement(node->elements[i]->mbr, rectAdd);

            // min area enlargement
            if (areaE < areaEnlarge)
            {
                areaMin = area;
                areaEnlarge = areaE;
                ele = i;
            }
            else if (areaE == areaEnlarge)
            {
                // if enlargement is same as min, we choose one with minimum area
                if (area < areaMin)
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
    while (!node->is_leaf)  // running loop until leaf is reached
    {
        node = chooseSubTree(node, rectAdd)->child;  // descends down to the leaf node
    }

    return node;  // correct leaf node
}
