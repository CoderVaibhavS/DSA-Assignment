#include <stdlib.h>
#include "rtree.h"

/* WRITE ALL THE FUNCTION IMPLEMENTATIONS HERE */
RTREE createRTree()
{
    
    RTREE r=(RTREE)malloc(sizeof(struct rtree));                     // initialising all parts of the firstnode of the R-Tree to 0
    r->height=0;
    r->root->count=0;
    for(int i=0;i<MAX_ENTRIES;i++){
        r->root->mbrs[i]->x_max=0;
        r->root->mbrs[i]->x_min=0;
        r->root->mbrs[i]->y_max=0;
        r->root->mbrs[i]->y_min=0;
    }
    for(int i=0;i<MAX_ENTRIES;i++){
        r->root->children[i]=0;
    }
}