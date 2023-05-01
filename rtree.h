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
typedef struct splitResult SplitResult;

struct point  // this struct basically represents any cartesian coordinate
{
    int x;
    int y;
};

// Assuming the coordinates to be integers
struct rectangle  // this struct represents a rectangle
{  // we have chosem topRight and bottomLeft points because these for the endpoints of a rectangle and are enough to
   // define a rectangle
    Point topRight;
    Point bottomLeft;
};

struct node_ele  // this is the struct which contains the MBR
{
    Rect mbr;
    Node *child;      // this represents the node that contains and encloses the children MBR
    Node *container;  // this represents the node which encapsulates our current MBR while containing many other MBRs
};

struct node  // this is the container which contains node_ele
{
    bool is_leaf;         // to check if the node is leaf or non-leaf
    int count;            // no of node_ele present
    Node_ele **elements;  // array of node_ele present within node
    Node_ele *parent;  // this basically represents the parent of the node which is node_ele or in other words the child
                       // in node_ele will point to this node
};

struct rtree  // structure which represents the r tree and contains the starting root node
{
    Node *root;
};

struct splitResult  // this is a temporary strct that we will use to help us with splitting of a node during insertion
                    // in the case of overflow
{
    Node_ele *parent;  // we are keeping track of the parent of the node which is basically node_ele and parent->child
                       // will be the current node that we are splitting
    Node *leaf1;       // leaf1 and leaf2 are the two nodes the initial node is splitting into
    Node *leaf2;
};

/* DECLARE ALL THE FUNCTION DEFINITIONS HERE */
Node_ele *createNodeEle(Node *container, Point topRight,
                        Point bottomLeft);  // these various methods will be explained wherever they were defined
Node *createNode(Node_ele *parent, bool isLeaf);
Rtree *createRtree();
void traversal(Node *root, bool isInit);

int calculateAreaOfRectangle(Rect rec);
Rect createMBR(Rect rect1, Rect rect2);
int calcAreaEnlargement(Rect rectCont, Rect rectChild);
void createNodeParent(Node *node);
Node_ele *chooseSubTree(Node *n, Rect r);
Node *ChooseLeaf(Rtree *r, Rect r1);
void updateParent(Node_ele *n, Node *n1, Node *n2);
SplitResult *nodeSplit(Node *node);
SplitResult *adjustTree(SplitResult *split);
bool isPresent(Node_ele **e1, int s, Node_ele *e2);
// int LeafCheck(Node *n);
// Node *descendTree(Node *n);
// Rect CalculateRecatangleMBR(Node *n);
// int CalculateOverlapArea(Rect rect1, Rect rect2);
// Node *ChooseLeaf(Node *n);

void pickSeeds(Node *node, Node *node1, Node *node2);
void pickNext(Node *node, Node *node1, Node *node2);

bool is_overlap(Rect r, Rect mbr);
void search(Node *search_node, Rect search_rect);
void insert(Rtree *r, Point p1, Point p2);

#endif
