#include <stdlib.h>
#include "rtree.h"

Rect create_rectangle(int x, int y){
    Rect *Rectangle = (Rect *)malloc(sizeof(Rect));
    Rectangle->bottomLeft.x = 40;
    Rectangle->bottomLeft.y = 40;
    Rectangle->topRight.x = 65;
    Rectangle->topRight.y = 65;
    return *Rectangle;
}
bool is_overlap(Rect r, Rect mbr)   //checks for an overlap between the rectangle and the MBR in a node
{
    if (r.bottomLeft.x < mbr.topRight.x && r.bottomLeft.y < mbr.topRight.y && r.topRight.x > mbr.bottomLeft.x && r.topRight.y > mbr.bottomLeft.y)
        return true;   
        // returns true if the bottomleft point of search rectangle is less than the topright of MBR and the topright of search rectangle is     greater than the bottom left of MBR
    return false;
}

void search(Node *search_node, Rect search_rect) //node of rtree and rectangle to be searched are passed as parameters to the search function
{
    for (int i = 0; i < search_node->count; i++) // iterates over the MBRs present in the passed node
    {
        if (is_overlap(search_rect, search_node->elements[i].mbr)) // checks for an overlap through the is_overlap function
        {
            printf(" %s overlapped MBR has index : %d and bottomleft and topright coords : (%d,%d) (%d,%d) \n", search_node->is_leaf == false ? "\n internal node - " : "   leaf node  - ", i + 1, search_node->elements[i].mbr.bottomLeft.x, search_node->elements[i].mbr.bottomLeft.y, search_node->elements[i].mbr.topRight.x, search_node->elements[i].mbr.topRight.y); 
            //if an overlap is found, the bottomleft and topright datapoints of the MBR is displayed along with the type of node the MBR is a part of
            if (search_node->is_leaf == false) 
            // if the passed node is a non-leaf node, then we first descent into the r-tree before searching in the MBRs at same level, passing the corresponding child of overlapping MBR as the root node of the subtree.
                search(search_node->elements[i].child, search_rect);
            else // if the passed node is a leaf node, we search the MBRs present in this leaf node for a possible overlap
                continue;
        }
    }
    return;
}

int main() {
 
    // the testing tree I used    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Rtree *rtree = (Rtree *)malloc(sizeof(Rtree));

    rtree->root = (Node *)malloc(sizeof(Node));
    rtree->root->count = 0;

    rtree->root->elements = (Node_ele *)malloc(MAX_ENTRIES * sizeof(Node_ele));
    rtree->root->elements[0].mbr.topRight.x = 100;
    rtree->root->elements[0].mbr.topRight.y = 100;
    rtree->root->elements[0].mbr.bottomLeft.x = 75;
    rtree->root->elements[0].mbr.bottomLeft.y = 75;
    rtree->root->count++;

    rtree->root->elements[1].mbr.topRight.x = 75;
    rtree->root->elements[1].mbr.topRight.y = 75;
    rtree->root->elements[1].mbr.bottomLeft.x = 50;
    rtree->root->elements[1].mbr.bottomLeft.y = 50;
    rtree->root->count++;

    rtree->root->elements[2].mbr.topRight.x = 50;
    rtree->root->elements[2].mbr.topRight.y = 50;
    rtree->root->elements[2].mbr.bottomLeft.x = 25;
    rtree->root->elements[2].mbr.bottomLeft.y = 25;
    rtree->root->count++;

    rtree->root->elements[3].mbr.topRight.x = 25;
    rtree->root->elements[3].mbr.topRight.y = 25;
    rtree->root->elements[3].mbr.bottomLeft.x = 0;
    rtree->root->elements[3].mbr.bottomLeft.y = 0;
    rtree->root->count++;

    rtree->root->is_leaf = false;

    Node *temp;
    /* -----------------------------------------CHILD 1---------------------------------------- */

    rtree->root->elements[0].child = (Node *)malloc(sizeof(Node));
    temp = rtree->root->elements[0].child;
    temp->count = 0;
    temp->is_leaf = true;
    temp->elements = (Node_ele *)malloc(MAX_ENTRIES * sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 95;
    temp->elements[0].mbr.topRight.y = 95;
    temp->elements[0].mbr.bottomLeft.x = 75;
    temp->elements[0].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node *)malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 90;
    temp->elements[1].mbr.topRight.y = 90;
    temp->elements[1].mbr.bottomLeft.x = 75;
    temp->elements[1].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node *)malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 85;
    temp->elements[2].mbr.topRight.y = 85;
    temp->elements[2].mbr.bottomLeft.x = 75;
    temp->elements[2].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node *)malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 80;
    temp->elements[3].mbr.topRight.y = 80;
    temp->elements[3].mbr.bottomLeft.x = 75;
    temp->elements[3].mbr.bottomLeft.y = 75;
    temp->count++;

    /* -----------------------------------------CHILD 2---------------------------------------- */

    rtree->root->elements[1].child = (Node *)malloc(sizeof(Node));
    temp = rtree->root->elements[1].child;
    temp->count = 0;
    temp->is_leaf = true;
    temp->elements = (Node_ele *)malloc(MAX_ENTRIES * sizeof(Node_ele));

    temp->elements[0].mbr.topRight.x = 70;
    temp->elements[0].mbr.topRight.y = 70;
    temp->elements[0].mbr.bottomLeft.x = 50;
    temp->elements[0].mbr.bottomLeft.y = 50;
    temp->count++;

    // rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 65;
    temp->elements[1].mbr.topRight.y = 65;
    temp->elements[1].mbr.bottomLeft.x = 50;
    temp->elements[1].mbr.bottomLeft.y = 50;
    temp->count++;

    // rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 60;
    temp->elements[2].mbr.topRight.y = 60;
    temp->elements[2].mbr.bottomLeft.x = 50;
    temp->elements[2].mbr.bottomLeft.y = 50;
    temp->count++;

    // rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 55;
    temp->elements[3].mbr.topRight.y = 55;
    temp->elements[3].mbr.bottomLeft.x = 50;
    temp->elements[3].mbr.bottomLeft.y = 50;
    temp->count++;

    /* -----------------------------------------CHILD 3---------------------------------------- */

    rtree->root->elements[2].child = (Node *)malloc(sizeof(Node));
    temp = rtree->root->elements[2].child;
    temp->count = 0;
    temp->is_leaf = true;
    temp->elements = (Node_ele *)malloc(MAX_ENTRIES * sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 45;
    temp->elements[0].mbr.topRight.y = 45;
    temp->elements[0].mbr.bottomLeft.x = 25;
    temp->elements[0].mbr.bottomLeft.y = 25;
    temp->count++;

    // rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 40;
    temp->elements[1].mbr.topRight.y = 40;
    temp->elements[1].mbr.bottomLeft.x = 25;
    temp->elements[1].mbr.bottomLeft.y = 25;
    temp->count++;

    // rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 35;
    temp->elements[2].mbr.topRight.y = 35;
    temp->elements[2].mbr.bottomLeft.x = 25;
    temp->elements[2].mbr.bottomLeft.y = 25;
    temp->count++;

    // rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 30;
    temp->elements[3].mbr.topRight.y = 30;
    temp->elements[3].mbr.bottomLeft.x = 25;
    temp->elements[3].mbr.bottomLeft.y = 25;
    temp->count++;

    /* -----------------------------------------CHILD 4---------------------------------------- */

    rtree->root->elements[3].child = (Node *)malloc(sizeof(Node));
    temp = rtree->root->elements[3].child;
    temp->count = 0;
    temp->is_leaf = true;
    temp->elements = (Node_ele *)malloc(MAX_ENTRIES * sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 20;
    temp->elements[0].mbr.topRight.y = 20;
    temp->elements[0].mbr.bottomLeft.x = 0;
    temp->elements[0].mbr.bottomLeft.y = 0;
    temp->count++;

    // rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 15;
    temp->elements[1].mbr.topRight.y = 15;
    temp->elements[1].mbr.bottomLeft.x = 0;
    temp->elements[1].mbr.bottomLeft.y = 0;
    temp->count++;

    // rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 10;
    temp->elements[2].mbr.topRight.y = 10;
    temp->elements[2].mbr.bottomLeft.x = 0;
    temp->elements[2].mbr.bottomLeft.y = 0;
    temp->count++;

    // rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 5;
    temp->elements[3].mbr.topRight.y = 5;
    temp->elements[3].mbr.bottomLeft.x = 0;
    temp->elements[3].mbr.bottomLeft.y = 0;
    temp->count++;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    Rect search_rect = create_rectangle(40,65); // creating rectangle for search

    printf("\nbottomleft and topright coords of search rectangle : (%d,%d) (%d,%d) \n", search_rect.bottomLeft.x, search_rect.bottomLeft.y, search_rect.topRight.x, search_rect.topRight.y); //displaying datapoints of search rectangle

    search(rtree->root,search_rect); //calling search function

}