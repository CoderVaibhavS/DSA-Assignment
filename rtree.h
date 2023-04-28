#ifndef RTREE_H
//------------------------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree Rtree;
typedef struct node Node;
typedef struct point Point;
typedef struct rectangle Rect;
typedef struct node_ele Node_ele;

struct point
{
    int x;
    int y;
};

// Assuming the coordinates to be integers
struct rectangle
{
    Point topRight;
    Point bottomLeft;
};

struct node_ele
{
    Rect mbr;
    Node *child;
    Node *container;
};

struct node
{
    bool is_leaf;
    int count;  // no of entries stored
    Node_ele **elements;
    Node_ele *parent;
};

struct rtree
{
    Node *root;
};

/* DECLARE ALL THE FUNCTION DEFINITIONS HERE */
Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft);
Node *createNode(Node_ele *parent);
Rtree *createRtree();
void traversal(Node* root);

int calculateAreaOfRectangle(Rect rec);
Rect CalculateRecatangleMBR(Node *n);
int CalculateOverlapArea(Rect rect1, Rect rect2);
Node *chooseSubTree(Node *n);
int LeafCheck(Node *n);
Node *descendTree(Node *n);
// Node *ChooseLeaf(Rtree *r, Rect r1);
Node *ChooseLeaf(Node *n);

void pickSeeds(Node* node, Node* node1, Node* node2);
void pickNext();

Rect create_rectangle(int xmin, int ymin, int xmax, int ymax);
bool is_overlap(Rect r, Rect mbr);
void search(Node *search_node, Rect search_rect);

#endif
