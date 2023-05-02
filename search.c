#include <stdlib.h>
#include "rtree.h"

bool isOverlap(Rect r, Rect mbr)  // checks for an overlap between the
                                   // rectangle and the MBR in a node
{
    if (r.bottomLeft.x <= mbr.topRight.x && r.bottomLeft.y <= mbr.topRight.y && r.topRight.x >= mbr.bottomLeft.x && r.topRight.y >= mbr.bottomLeft.y)
        return true;

    return false;
}

void search(Node *search_node, Rect search_rect) 
{
    for (int i = 0; i < search_node->count; i++)  // iterates over the MBRs present in the passed node
    {
        if (&search_node->elements[i] != NULL &&
            isOverlap(search_rect,
                      search_node->elements[i]->mbr))  // checks for an overlap through
                                                        // the is_overlap function
        {
            if (search_node->parent == NULL)  // overlapped MBR is from a root node
            {
                printf("%s overlapped MBR index : %d, BottomLeft & TopRight bounds : (%d,%d) (%d,%d) \n",
                       "\nRoot node - ", i + 1, search_node->elements[i]->mbr.bottomLeft.x,
                       search_node->elements[i]->mbr.bottomLeft.y, search_node->elements[i]->mbr.topRight.x,
                       search_node->elements[i]->mbr.topRight.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }
            else if (search_node->is_leaf == false)  // overlapped MBR is from an internal node
            {
                printf("%s overlapped MBR index : %d, BottomLeft & TopRight bounds : (%d,%d) (%d,%d) \n",
                       " --> internal node - ", i + 1, search_node->elements[i]->mbr.bottomLeft.x,
                       search_node->elements[i]->mbr.bottomLeft.y, search_node->elements[i]->mbr.topRight.x,
                       search_node->elements[i]->mbr.topRight.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }
            else  // overlapped MBR is part of a leaf node (datapoint)
            {
                printf(" %s overlapped datapoint index : %d, datapoint : (%d,%d) \n", "   ----> leaf node - ", i + 1,
                       search_node->elements[i]->mbr.bottomLeft.x, search_node->elements[i]->mbr.bottomLeft.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }

            if (search_node->elements[i]->child != NULL && search_node->is_leaf == false)
                search(search_node->elements[i]->child, search_rect);
            // if the passed node is a non-leaf node, then we first descent
            // into the r-tree before searching in the MBRs at same level,
            // passing the corresponding child of overlapping MBR as the
            // root node of the subtree.

            else  // if the passed node is a leaf node, we search the MBRs
                  // present in this leaf node for a possible overlap
                continue;
        }
    }
    return;
}