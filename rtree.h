#ifndef RTREE_H
#define RTREE_H

// Maximum and minimum entries that can be accomodated in a rectangle
#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree* RTREE;
typedef struct node* NODE;
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

// Assuming the coordinates to be integers
struct mbr {
    // Min and max coordinates of the rectangle
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};

/* DECLARE ALL THE FUNCTION DEFINITIONS HERE */

#endif