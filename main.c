#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtree.h"

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

/* -----------------------------------------------STRUCTURE------------------------------------------------------------*/
typedef struct rtree Rtree;
typedef struct node Node;
typedef struct point Point;
typedef struct rectangle Rect;
typedef struct node_ele Node_ele;

// struct point
// {
//     int x;
//     int y;
// };
//
// // Assuming the coordinates to be integers
// struct rectangle
// {
//     Point topRight;
//     Point bottomLeft;
// };
//
// struct node_ele
// {
//     Rect mbr;
//     Node *child;
//     Node *container;
// };
//
// struct node
// {
//     bool is_leaf;
//     int count;  // no of entries stored
//     Node_ele **elements;
//     Node_ele *parent;
// };
//
// struct rtree
// {
//     Node *root;
// };
//
/* --------------------------------------------------GENERATING
 * FUNCTIONS---------------------------------------------------- */

Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft)  // function to create a node_ele
{
    Node_ele *node_ele = (Node_ele *)malloc(sizeof(Node_ele));  // dynamically allocating memory
    node_ele->container = container;                            // initializing all the parameters with
    node_ele->child = NULL;                                     // appropriate values
    node_ele->mbr.bottomLeft = bottomLeft;
    node_ele->mbr.topRight = topRight;

    return node_ele;
}

// Creating Node function

Node *createNode(Node_ele *parent, bool isLeaf)
{
    Node *node = (Node *)malloc(sizeof(Node));  // creating a node dynamically

    node->is_leaf = isLeaf;  // initializing all the fields of the struct node.
    node->count = 0;         // initial count=0
    node->elements = (Node_ele **)malloc((MAX_ENTRIES + 1) * sizeof(Node_ele *));
    node->parent = parent;  // initializing parent
    // node->parent->container->is_leaf = false;

    return node;  // returning the node
}

// creating R Tree function
Rtree *createRtree()  // No parameters required to create a rtree
{
    Rtree *rtree = (Rtree *)malloc(sizeof(Rtree));  // Creating r tree dynamically
    rtree->root = createNode(NULL, true);           // Only node is the root itself,hence it's a leaf node.

    return rtree;  // returning the tree
}

/* ----------------------------------------------PREORDER TRAVERSAL----------------------------------------------------
 */
// defining preorder - first, list all the current node elements -> then, traverse all the children
void traversal(Node *root, bool isInit)  // code for pre order traversal
{
    if (root == NULL) return;  // simply returning if root is null
    Rect mbr;
    mbr = root->elements[0]->mbr;
    // Calculate the parent's MBR by repeatedly checking max and min value of container of previous MBRs and current MBR
    if (isInit)
    {
        for (int i = 1; i < root->count; i++)
        {
            mbr = createMBR(mbr, root->elements[i]->mbr);

        }  // or in otherwords creates the parent MBR structure from where are current root descended from
        printf("Tree MBR: (%d, %d) -> (%d, %d)", mbr.bottomLeft.x, mbr.bottomLeft.y, mbr.topRight.x, mbr.topRight.y);
    }

    if (root->is_leaf) printf("\nLeaf Node: ");

    for (int i = 0; i < root->count; i++)  // iterating through all elements of the root
    {
        Rect rect = root->elements[i]->mbr;
        if (root->is_leaf)  // if leaf node
        {
            if (rect.topRight.x == rect.bottomLeft.x && rect.topRight.y == rect.bottomLeft.y)
            {
                printf("(%d, %d) ", rect.topRight.x, rect.topRight.y);
            }
            else
            {
                printf("(%d, %d) -> (%d, %d) ", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
            }
        }
        else if (root->parent == NULL)  // if root node
        {
            printf("\n\nRoot Node Element: ");
            printf("(%d, %d) -> (%d, %d)", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }
        else  // if internal node
        {
            printf("\nInternal Node Element: ");
            printf("(%d, %d) -> (%d, %d)", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }
        if (!root->is_leaf)
            traversal(root->elements[i]->child, false);  // recursively traverse through the whole tree by calling
    }
    if (isInit) printf("\n");
}
//--------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    FILE *fp = fopen("data.txt", "r");
    Rect mbr;
    int x, y;
    Rtree *tree = createRtree();
    while (fscanf(fp, "%d %d\n", &x, &y) != EOF)
    {
        Point bottomLeft = {x, y};
        Point topRight = {x, y};
        insert(tree, bottomLeft, topRight);
    }
    fclose(fp);
    traversal(tree->root, true);
    return 0;
}
