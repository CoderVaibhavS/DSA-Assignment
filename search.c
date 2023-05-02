#include <math.h>
#include <stdlib.h>

#include "rtree.h"

// checks for an overlap between the rectangle and the MBR in a node
bool isOverlap(Rect r, Rect mbr)
{
    int xMin = fmax(r.bottomLeft.x, mbr.bottomLeft.x);
    int xMax = fmin(r.topRight.x, mbr.topRight.x);
    int yMin = fmax(r.bottomLeft.y, mbr.bottomLeft.y);
    int yMax = fmin(r.topRight.y, mbr.topRight.y);
    if (xMin <= xMax && yMin <= yMax) return true;
    return false;
}

// searches for searchRect in searchNode
void search(Node *searchNode, Rect searchRect)
{
    for (int i = 0; i < searchNode->count; i++)  // iterates over the MBRs present in the passed node
    {
        if (searchNode->elements[i] != NULL && isOverlap(searchRect, searchNode->elements[i]->mbr))
        {
            if (searchNode->is_leaf)  // overlapped MBR is part of a leaf node (datapoint)
            {
                if (searchNode->elements[i]->mbr.topRight.x == searchNode->elements[i]->mbr.bottomLeft.x &&
                    searchNode->elements[i]->mbr.topRight.y == searchNode->elements[i]->mbr.bottomLeft.y)
                    printf("Search MBR overlaps with leaf element: (%d, %d)\n", searchNode->elements[i]->mbr.topRight.x,
                           searchNode->elements[i]->mbr.topRight.y);
                else
                    printf("Search MBR overlaps with leaf element: (%d, %d) -> (%d, %d)\n",
                           searchNode->elements[i]->mbr.bottomLeft.x, searchNode->elements[i]->mbr.bottomLeft.y,
                           searchNode->elements[i]->mbr.topRight.x, searchNode->elements[i]->mbr.topRight.y);
            }

            // Descend into tree if node is not leaf
            if (searchNode->elements[i]->child != NULL && searchNode->is_leaf == false)
                search(searchNode->elements[i]->child, searchRect);
        }
    }
}
