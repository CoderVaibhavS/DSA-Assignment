#include <stdlib.h>

#include "rtree.h"

Rect create_rectangle(int xmin, int ymin, int xmax, int ymax)
{
    Rect *Rectangle = (Rect *)malloc(sizeof(Rect));
    Rectangle->bottomLeft.x = xmin;
    Rectangle->bottomLeft.y = ymin;
    Rectangle->topRight.x = xmax;
    Rectangle->topRight.y = ymax;
    return *Rectangle;
}
bool is_overlap(Rect r, Rect mbr)  // checks for an overlap between the
                                   // rectangle and the MBR in a node
{
    if (r.bottomLeft.x < mbr.topRight.x && r.bottomLeft.y < mbr.topRight.y &&
        r.topRight.x > mbr.bottomLeft.x && r.topRight.y > mbr.bottomLeft.y)
        return true;
    // returns true if the bottomleft point of search rectangle is less than the
    // topright of MBR and the topright of search rectangle is     greater than
    // the bottom left of MBR
    return false;
}

void search(Node *search_node,
            Rect search_rect)  // node of rtree and rectangle to be searched are
                               // passed as parameters to the search function
{
    for (int i = 0; i < search_node->count;
         i++)  // iterates over the MBRs present in the passed node
    {
        if (is_overlap(
                search_rect,
                search_node->elements[i].mbr))  // checks for an overlap through
                                                // the is_overlap function
        {
            printf(
                " %s overlapped MBR has index : %d and bottomleft and topright "
                "coords : (%d,%d) (%d,%d) \n",
                search_node->is_leaf == false ? "\n internal node - "
                                              : "   leaf node  - ",
                i + 1, search_node->elements[i].mbr.bottomLeft.x,
                search_node->elements[i].mbr.bottomLeft.y,
                search_node->elements[i].mbr.topRight.x,
                search_node->elements[i].mbr.topRight.y);
            // if an overlap is found, the bottomleft and topright datapoints of
            // the MBR is displayed along with the type of node the MBR is a
            // part of
            if (search_node->is_leaf == false)
                // if the passed node is a non-leaf node, then we first descent
                // into the r-tree before searching in the MBRs at same level,
                // passing the corresponding child of overlapping MBR as the
                // root node of the subtree.
                search(search_node->elements[i].child, search_rect);
            else  // if the passed node is a leaf node, we search the MBRs
                  // present in this leaf node for a possible overlap
                continue;
        }
    }
    return;
}
