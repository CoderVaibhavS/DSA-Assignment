#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

/* -----------------------------------------------STRUCTURE------------------------------------------------------------*/
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

/* --------------------------------------------------GENERATING FUNCTIONS---------------------------------------------------- */

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

/* ----------------------------------------------PREORDER TRAVERSAL---------------------------------------------------- */
void traversal(Node* root) {
    if(root == NULL)    return;

    for (int i = 0; i < root->count; i++) {
        Rect rect = root->elements[i]->mbr;
        if(root->elements[i]->container->parent == NULL) {
            printf("Root Node Element: ");
            printf("%d %d %d %d\n", rect.topRight.x, rect.topRight.y, rect.bottomLeft.x, rect.bottomLeft.y);
        }
        else if(root->elements[i]->container->is_leaf) {
            printf("Leaf Node Element: ");
            printf("%d %d\n", rect.topRight.x, rect.topRight.y);
        }
        else {
            printf("Internal Node Element: ");
            printf("%d %d %d %d\n", rect.topRight.x, rect.topRight.y, rect.bottomLeft.x, rect.bottomLeft.y);
        }
        if (!root->is_leaf) traversal(root->elements[i]->child);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------
