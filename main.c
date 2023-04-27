/* ------------------------------------------------------------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree Rtree;
typedef struct node Node;
typedef struct point Point;
typedef struct rectangle Rect;
typedef struct node_ele Node_ele;

struct point {
    int x;
    int y;
};

// Assuming the coordinates to be integers
struct rectangle {
    Point topRight;
    Point bottomLeft;
};

struct node_ele {
    Rect mbr;
    Node *child;
};

struct node {
    bool is_leaf;
    int count; // no of entries stored
    Node_ele *elements;
    // add parent node if required
};

struct rtree {
    Node *root;
};

//------------------------------------------------------------------------------------------------------------------------------------------
// creating R Tree function
Rtree *createRTree()
{

    Rtree *r = (Rtree *) malloc(sizeof(Rtree)); // initialising all parts of the firstnode of the R-Tree to 0
    r->root = (Node *) malloc(sizeof(Node));
    r->root = NULL;
    r->root->count = 0;
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