#ifndef RTREE_H
//------------------------------------------------------------------------------------------------------------------------
//The dashes like the one shown above show important demarcations and boundaries to make the code readable
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
    Node* child;
};

struct node {
    bool is_leaf;
    int count;      // no of entries stored
    Node_ele* elements;
    // add parent node if required
};

struct rtree {
    Node* root;
};


/* DECLARE ALL THE FUNCTION DEFINITIONS HERE */
Rtree createRTree();
int CalculateAreaOfrectangle(Rect rec);
Node* chooseSubTree(Node* n);
int LeafCheck(Node* n);
Node* descendTree(Node* n);
Rect ChooseLeaf(Node* r);

void pickSeeds(Node* node, Rect* r1, Rect* r2);

Rect create_rectangle(int xmin, int ymin, int xmax,int ymax);
bool is_overlap(Rect r, Rect mbr);
void search(Node *search_node, Rect search_rect);

#endif
