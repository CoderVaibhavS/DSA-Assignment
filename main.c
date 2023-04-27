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
};

struct node
{
    bool is_leaf;
    int count; // no of entries stored
    Node_ele *elements;
    // add parent node if required
    Node *parent;
};

struct rtree
{
    Node *root;
};

//------------------------------------------------------------------------------------------------------------------------------------------
// creating R Tree function

Rtree *createRtree() // No parameters required to create a rtree
{
    Rtree *rtree = malloc(sizeof(Rtree)); // Creating r tree dynamically
    Node *root = malloc(sizeof(Node));    // Creating root node dynamically

    root->is_leaf = true; // Only node is the root itself,hence it's a leaf node.
    root->count = 0;      // Initial count is zero as no children added to the root.
    root->parent = NULL;  // Root is itself at the topmost level.
    rtree->root = root;   // Initializing root

    return rtree; // returning the tree
}

// Creating Node function

Node *createNode(bool is_leaf, Node *parent) // takes 2 parameters
{
    Node *node = malloc(sizeof(Node)); // creating a node dynamically

    node->is_leaf = is_leaf; // initializing all the fiels of the struct node.
    node->count = 0;         // initial count=0
    node->elements = NULL;   // initially no elements in the node
    node->parent = parent;   // initializing parent

    return node; // returning the node
}

//--------------------------------------------------------------------------------------------------------------------------------------

int main()
{
}