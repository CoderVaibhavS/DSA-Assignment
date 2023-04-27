//------------------------------------------------------------------------------------------------------------------------
//The dashes like the one shown above show important demarcations and boundaries to make the code readable
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree* RTREE;
typedef struct node* NODE;
typedef struct point* POINT;
typedef struct mbr* MBR;

struct rtree {
    NODE root;
    int height;
};

struct node {
    int count;      // no of entries stored
    MBR mbrs[MAX_ENTRIES];      // array of MBRs of the keys of the node
    NODE children[MAX_ENTRIES];     // array of children nodes
};

struct point {
    int x;
    int y;
};

// Assuming the coordinates to be integers
struct mbr {
    // Min and max coordinates of the rectangle
    // int x_min;
    // int x_max;
    // int y_min;
    // int y_max;
    POINT topRight;
    POINT bottomLeft;
};

//------------------------------------------------------------------------------------------------------------------------------------------
//creating R Tree function
RTREE createRTree()
{
    
    RTREE r=(RTREE)malloc(sizeof(struct rtree));                     // initialising all parts of the firstnode of the R-Tree to 0
    r->height=0;
    r->root = (NODE)malloc(sizeof(struct node));
    r->root=NULL;
    r->root->count=0;
    // for(int i=0;i<MAX_ENTRIES;i++){
    //     r->root->mbrs[i]->x_max=0;
    //     r->root->mbrs[i]->x_min=0;
    //     r->root->mbrs[i]->y_max=0;
    //     r->root->mbrs[i]->y_min=0;
    // }
    // for(int i=0;i<MAX_ENTRIES;i++){
    //     r->root->children[i]=NULL;
    // }
    return r;
}

 //--------------------------------------------------------------------------------------------------------------------------------------


int main() {
    
}