#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtree.h"

// Insertion function with necessary helper functions.

int CalculateAreaOfMBR(Rect rect)  // Returns the area of the rectangle
{
    int length = abs(rect.topRight.x -
                     rect.bottomLeft.x);  // this is length of rectangle
    int width =
        abs(rect.topRight.y - rect.bottomLeft.y);  // this is width of rectangle
    int area = (length * width);  // area of rectangle= length *breadth
    return area;                  // returns area of the rectangle
}

Rect CalculateRecatangleMBR(
    Node *n)  // Calculating the minimum bounding rectangle function
{
    Rect r_mbr;

    r_mbr.topRight.x = -1;  // initializing all the values with -1 initially
    r_mbr.topRight.y = -1;
    r_mbr.bottomLeft.x = -1;
    r_mbr.bottomLeft.y = -1;

    for (int i = 0; i < n->count; i++)  // Traversing the whole node (all the
                                        // entries of a particular node)
    {
        if (i == 0)  // case when only one rectangle
        {
            r_mbr = n->elements[i].mbr;
        }
        else  // handling the other cases
        {
            if (r_mbr.topRight.x < n->elements[i].mbr.topRight.x)
            {
                r_mbr.topRight.x =
                    n->elements[i].mbr.topRight.x;  // assign the value if
                                                    // condition satisfies
            }
            else
            {
                r_mbr.topRight.x =
                    r_mbr.topRight.x;  // if condition doesn't satisfy ,it
                                       // remains unchanged
            }
            if (r_mbr.topRight.y < n->elements[i].mbr.topRight.y)
            {
                r_mbr.topRight.y = n->elements[i].mbr.topRight.y;
            }
            else
            {
                r_mbr.topRight.y = r_mbr.topRight.y;
            }
            if (r_mbr.bottomLeft.x > n->elements[i].mbr.bottomLeft.x)
            {
                r_mbr.bottomLeft.x = n->elements[i].mbr.bottomLeft.x;
            }
            else
            {
                r_mbr.bottomLeft.x = r_mbr.bottomLeft.x;
            }
            if (r_mbr.bottomLeft.y > n->elements[i].mbr.bottomLeft.y)
            {
                r_mbr.bottomLeft.y = n->elements[i].mbr.bottomLeft.y;
            }
            else
            {
                r_mbr.bottomLeft.y = r_mbr.bottomLeft.y;
            }
        }
    }
    return r_mbr;
}

int CalculateOverlapArea(Rect rect1, Rect rect2)  // Overlapping area function
{
    int x1 = max(0, min(rect1.topRight.x, rect2.topRight.x));
    int x2 = max(rect1.bottomLeft.x, rect2.bottomLeft.x);
    int y1 = max(0, min(rect1.topRight.y, rect2.topRight.y));
    int y2 = max(rect1.bottomLeft.y, rect2.bottomLeft.y);

    int xOverlap = x1 - x2;
    int yOverlap = y1 - y2;
    int overlap = xOverlap * yOverlap;

    return overlap;
}

Node *ChooseLeaf(Rtree *rtree, Rect rect)
{
    Node *node = rtree->root;  // initializing  node to root as per step-1 of
                               // choose leaf in the research paper

    if (node->is_leaf)  // if node is a leaf node then return that according to
                        // step 2 of choose leaf in research paper
    {
        return node;
    }
    while (!node->is_leaf)  // else part when node is not a leaf nodes
    {
        float minOverlap =
            -1.0;  // initialize minimum overlap value and index values and
                   // storing in float variable as overlap may be in decimal
        int minIndex = -1;

        for (int i = 0; i < node->count;
             i++)  // iterate through each entry of the node and calculate the
                   // overlap with the given rectangle
        {
            Rect mbr = CalculateRecatangleMBR(node->elements[i].child);
            float overlap = CalculateOverlapArea(mbr, rect);

            if (minOverlap < 0 ||
                overlap <=
                    minOverlap)  // update minimum overlap and index if overlap
                                 // is smaller or equal to minOverlap

            {
                minOverlap = overlap;
                minIndex = i;
            }
        }
        node = node->elements[minIndex].child;  // moving down to the child node
                                                // with the smallest overlap
    }
    return node;
}
