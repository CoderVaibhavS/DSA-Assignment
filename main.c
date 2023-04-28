/* -----------------------------------------------STRUCTURE--------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------------------------------------------------

Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft) {
    Node_ele *node_ele = (Node_ele *) malloc(sizeof(Node_ele));
    node_ele->container = container;
    node_ele->child = NULL;
    node_ele->mbr.bottomLeft = bottomLeft;
    node_ele->mbr.topRight = topRight;

    return node_ele;
}

// Creating Node function

Node *createNode(Node_ele *parent)
{
    Node *node = (Node *) malloc(sizeof(Node));  // creating a node dynamically

    node->is_leaf = true;  // initializing all the fiels of the struct node.
    node->count = 0;          // initial count=0
    node->elements = (Node_ele **) malloc((MIN_ENTRIES) * sizeof(Node_ele *));  // initially no elements in the node
    node->parent = parent;  // initializing parent
    // node->parent->container->is_leaf = false;

    return node;  // returning the node
}

// creating R Tree function
Rtree *createRtree()  // No parameters required to create a rtree
{
    Rtree *rtree = (Rtree *) malloc(sizeof(Rtree));  // Creating r tree dynamically
    rtree->root = createNode(NULL);  // Only node is the root itself,hence it's a leaf node.

    return rtree;  // returning the tree
}

//--------------------------------------------------------------------------------------------------------------------------------------

int main() {}
