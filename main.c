#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtree.h"

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

/* -----------------------------------------------STRUCTURE----------------------------------------------------------- */
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
/* --------------------------------------------------GENERATING FUNCTIONS---------------------------------------------------- */
// create node element
Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft)
{
    Node_ele *node_ele = (Node_ele *) malloc(sizeof(Node_ele));
    node_ele->container = container;                            
    node_ele->child = NULL;
    node_ele->mbr.bottomLeft = bottomLeft;
    node_ele->mbr.topRight = topRight;

    return node_ele;
}

// create node
Node *createNode(Node_ele *parent, bool isLeaf)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->is_leaf = isLeaf;
    node->count = 0;
    node->elements = (Node_ele **) malloc((MAX_ENTRIES + 1) * sizeof(Node_ele *));
    node->parent = parent;

    return node; 
}

// create tree
Rtree *createRtree()
{
    Rtree *rtree = (Rtree *) malloc(sizeof(Rtree));
    rtree->root = createNode(NULL, true);   // parent of root initialised to NULL

    return rtree;
}

/* ----------------------------------------------PREORDER TRAVERSAL---------------------------------------------------- */
// defining preorder - first, list all the current node elements -> then, traverse all the children in the same manner
void traversal(Node *root, bool isInit)
{
    if (root == NULL) return;
    Rect mbr;
    mbr = root->elements[0]->mbr;
    // Calculate the parent's MBR by repeatedly checking max and min value of container of previous MBRs and current MBR
    if (isInit)     // only for 1st level
    {
        for (int i = 1; i < root->count; i++)
        {
            mbr = createMBR(mbr, root->elements[i]->mbr);

        }  // or in otherwords creates the parent MBR structure from where are current root descended from
        printf("Tree MBR: (%d, %d) -> (%d, %d)\n", mbr.bottomLeft.x, mbr.bottomLeft.y, mbr.topRight.x, mbr.topRight.y);
    }

    for (int i = 0; i < root->count; i++)  // printing all elements of the root
    {
        Rect rect = root->elements[i]->mbr;

        if (root->elements[i]->container->is_leaf)  // leaf node
        {
            printf("Leaf Node Element: ");
            if (rect.topRight.x == rect.bottomLeft.x && rect.topRight.y == rect.bottomLeft.y)
            {
                printf("%d %d\n", rect.topRight.x, rect.topRight.y);
            }
            else
            {
                printf("(%d, %d) -> (%d, %d)\n", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x,
                       rect.topRight.y);
            }
        }
        else if (root->elements[i]->container->parent == NULL)  // root node
        {
            printf("Root Node Element: ");
            printf("(%d, %d) -> (%d, %d)\n", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }

        else  // internal node
        {
            printf("Internal Node Element: ");
            printf("(%d, %d) -> (%d, %d)\n", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }
    }

    // traverse through all the children of current node
    for (int i = 0; i < root->count; i++)
    {
        if (!root->is_leaf)
            traversal(root->elements[i]->child, false);
    }
}

/* ----------------------------------------------------------MAIN FUNCTION--------------------------------------------------------- */

int main()
{
    FILE *fp = fopen("data.txt", "r");
    Rect mbr;
    int x, y;
    Rtree *tree = createRtree();

    // insert all the points
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
