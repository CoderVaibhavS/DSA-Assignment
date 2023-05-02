#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "rtree.h"

// create an MBR for two rectangles
Rect createMBR(Rect rect1, Rect rect2)
{
    Rect rect;
    rect.topRight.x = fmax(rect1.topRight.x, rect2.topRight.x);
    rect.topRight.y = fmax(rect1.topRight.y, rect2.topRight.y);
    rect.bottomLeft.x = fmin(rect1.bottomLeft.x, rect2.bottomLeft.x);
    rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);

    return rect;
}

// area of a rectangle
int calculateAreaOfRectangle(Rect rect)
{
    int height = abs(rect.topRight.x - rect.bottomLeft.x);
    int width = abs(rect.topRight.y - rect.bottomLeft.y);
    return height * width;
}

// enlargement area for a rectangle to accomodate another rectangle
int calcAreaEnlargement(Rect rectCont, Rect rectChild)
{
    Rect enlargedRect = createMBR(rectCont, rectChild);
    return calculateAreaOfRectangle(enlargedRect) - calculateAreaOfRectangle(rectCont);
}

// Create a parent Node_ele (MBR) for node.
void createNodeParent(Node *node)
{
    Rect mbr;
    NodeEle *oldParent = node->parent;
    mbr = node->elements[0]->mbr;

    // Calculate the parent's MBR by repeatedly checking max and min value of container of previous MBRs and current MBR
    for (int i = 1; i < node->count; i++)
    {
        mbr = createMBR(mbr, node->elements[i]->mbr);
    }
    NodeEle *parent = createNodeEle(NULL, mbr.topRight, mbr.bottomLeft);

    node->parent = parent;
    parent->child = node;
    parent->mbr = mbr;
    if (oldParent != NULL)
    {
        node->parent->container = oldParent->container;
        free(oldParent);
    }
}

// Update node1 and node2 parent MBRs in container of parent MBR
void updateParent(NodeEle *parent, Node *node1, Node *node2)
{
    Node *parentNode = parent->container;
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

    parentNode->elements[ele] = node1->parent;
    node1->parent->container = parentNode;

    // If node did not split
    if (node1 != node2)
    {
        parentNode->elements[parentNode->count++] = node2->parent;
        node2->parent->container = parentNode;
        // createNodeParent already frees parent in case of no split
        free(parent);
    }
}
