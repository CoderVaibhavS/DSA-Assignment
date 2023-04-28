#include <math.h>
#include <stdio.h>

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
        {
            break;
        }
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
