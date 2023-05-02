#ifndef RTREE_H
/* ------------------------------------------------------------------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree Rtree;
typedef struct node Node;
typedef struct point Point;
typedef struct rectangle Rect;
typedef struct nodeEle NodeEle;
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
struct nodeEle
{
    Rect mbr;
    Node *child;
    Node *container;  // node which encapsulates the current MBR
};

// Node contains multiple node elements
struct node
{
    bool isLeaf;        // leaf or non-leaf
    int count;           // no of node_ele present
    NodeEle **elements;  // array of node_ele present within node
    NodeEle *parent;     // parent element of node
};

// Tree structure having root node
struct rtree
{
    Node *root;
};

// Temporary struct used to help with node splitting to propagate data up the tree
struct splitResult
{
    NodeEle *parent;  // parent of the node before splitting
    // leaf1 and leaf2 are the two splits of node
    Node *leaf1;
    Node *leaf2;
};

/* -------------------------FUNCTION DEFINITIONS--------------------------- */
NodeEle *createNodeEle(Node *container, Point topRight, Point bottomLeft);
Node *createNode(NodeEle *parent, bool isLeaf);
Rtree *createRtree();

void traversal(Node *root, bool isInit);

int calculateAreaOfRectangle(Rect rec);
Rect createMBR(Rect rect1, Rect rect2);
int calcAreaEnlargement(Rect rectCont, Rect rectChild);
void createNodeParent(Node *node);
void updateParent(NodeEle *n, Node *n1, Node *n2);

NodeEle *chooseSubTree(Node *n, Rect r);
Node *ChooseLeaf(Rtree *r, Rect r1);

void pickSeeds(Node *node, Node *node1, Node *node2);
void pickNext(Node *node, Node *node1, Node *node2);
SplitResult *nodeSplit(Node *node);
bool isPresent(NodeEle **e1, int s, NodeEle *e2);

SplitResult *adjustTree(SplitResult *split);

bool isOverlap(Rect r, Rect mbr);
void search(Node *search_node, Rect search_rect);

void insert(Rtree *r, Point p1, Point p2);
#endif
