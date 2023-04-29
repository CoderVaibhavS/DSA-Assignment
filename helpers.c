#include <math.h>
#include <stdio.h>

#include "rtree.h"

Rect createMBR(Rect rect1, Rect rect2)
{
    Rect rect;
    rect.topRight.x = fmax(rect1.topRight.x, rect2.topRight.x);  // we are doing this to find the rectangle of
                                                                 // smallest area that encloses rect1 and rect2
    rect.topRight.y = fmax(rect1.topRight.y, rect2.topRight.y);
    rect.bottomLeft.x = fmin(rect1.bottomLeft.x, rect2.bottomLeft.x);
    rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);

    return rect;
}

int calculateAreaOfRectangle(Rect rect)
{
    int height = abs(rect.topRight.x - rect.bottomLeft.x);
    int width = abs(rect.topRight.y - rect.bottomLeft.y);
    return height * width;
}

int calcAreaEnlargement(Rect rectCont, Rect rectChild)
{
    Rect enlargedRect = createMBR(rectCont, rectChild);
    return calculateAreaOfRectangle(enlargedRect) - calculateAreaOfRectangle(rectCont);
}

void createNodeParent(Node *node)
{
    Node_ele *parent = (Node_ele *)malloc(sizeof(Node_ele));
    Rect mbr;
    parent->child = node;
    parent->container = NULL;
    node->parent = parent;
    mbr = node->elements[0]->mbr;
    for (int i = 1; i < node->count; i++)
    {
        mbr = createMBR(mbr, node->elements[i]->mbr);
    }
    parent->mbr = mbr;
}
