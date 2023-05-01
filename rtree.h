#ifndef RTREE_H
/* ------------------------------------------------------------------------------------------------------------------------ */

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
typedef struct splitResult SplitResult;

// Assuming the coordinates to be integers
// This struct represents the cartesian coordinates of a point
struct point
{
    int x;
    int y;
};

// A rectangle has two corner points - TopLeft & BottomRight (Assuming the sides to be parallel to x and y axes)
struct rectangle 
{
    Point topRight;
    Point bottomLeft;
};

// Element of a node that has an MBR and child node
struct node_ele
{
    Rect mbr;
    Node *child;
    Node *container;  // node which encapsulates the current MBR
};

// Node contains multiple node elements
struct node
{
    bool is_leaf;         // leaf or non-leaf
    int count;            // no of node_ele present
    Node_ele **elements;  // array of node_ele present within node
    Node_ele *parent;   // parent element of node
};

// Tree structure having root node
struct rtree
{
    Node *root;
};

// Temporary struct used to help with node splitting to propagate data up the tree
struct splitResult 
{
    Node_ele *parent;  // parent of the node before splitting
    Node *leaf1;       // leaf1 and leaf2 are the two splitted nodes
    Node *leaf2;
};

/* -----------------------------------------------FUNCTION DEFINITIONS--------------------------------------------------- */
Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft);
Node *createNode(Node_ele *parent, bool isLeaf);
Rtree *createRtree();

void traversal(Node *root, bool isInit);

int calculateAreaOfRectangle(Rect rec);
Rect createMBR(Rect rect1, Rect rect2);
int calcAreaEnlargement(Rect rectCont, Rect rectChild);

Node_ele *chooseSubTree(Node *n, Rect r);
Node *ChooseLeaf(Rtree *r, Rect r1);

void pickSeeds(Node *node, Node *node1, Node *node2);
void pickNext(Node *node, Node *node1, Node *node2);
SplitResult *nodeSplit(Node *node);

void createNodeParent(Node *node);
void updateParent(Node_ele *n, Node *n1, Node *n2);
SplitResult *adjustTree(SplitResult *split);
bool isPresent(Node_ele **e1, int s, Node_ele *e2);

bool is_overlap(Rect r, Rect mbr);
void search(Node *search_node, Rect search_rect);
void insert(Rtree *r, Point p1, Point p2);

#endif