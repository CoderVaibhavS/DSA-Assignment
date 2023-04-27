#ifndef RTREE_H
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

/* DECLARE ALL THE FUNCTION DEFINITIONS HERE */
RTREE createRTree();
int CalculateAreaOfMBR(MBR rec);
MBR chooseSubTree(NODE n);
int LeafCheck(NODE n);
NODE descendTree(NODE n);
MBR ChooseLeaf(NODE r);

#endif