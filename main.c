#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtree.h"

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

/* -----------------------------------------------STRUCTURE-----------------------------------------------------------
 */
typedef struct rtree Rtree;
typedef struct node Node;
typedef struct point Point;
typedef struct rectangle Rect;
typedef struct nodeEle NodeEle;

/* --------------------------------------------GENERATING FUNCTIONS---------------------------------------------------
 */
// create node element
NodeEle *createNodeEle(Node *container, Point topRight, Point bottomLeft)
{
    NodeEle *node_ele = (NodeEle *)malloc(sizeof(NodeEle));
    node_ele->container = container;
    node_ele->child = NULL;
    node_ele->mbr.bottomLeft = bottomLeft;
    node_ele->mbr.topRight = topRight;
    return node_ele;
}
// create node
Node *createNode(NodeEle *parent, bool isLeaf)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->is_leaf = isLeaf;
    node->count = 0;
    // MAX_ENTRIES + 1 to ensure space for 5th elements right before splitting
    node->elements = (NodeEle **)malloc((MAX_ENTRIES + 1) * sizeof(NodeEle *));
    node->parent = parent;
    return node;  // returning the node
}
// create tree with empty root
Rtree *createRtree()
{
    Rtree *rtree = (Rtree *)malloc(sizeof(Rtree));
    rtree->root = createNode(NULL, true);
    return rtree;
}

/* ----------------------------------------------PREORDER TRAVERSAL----------------------------------------------------
 */
// defining preorder - first, list all the current node elements -> then, traverse all the children in the same manner
void traversal(Node *root, bool isInit)
{
    if (root == NULL) return;
    Rect mbr;
    mbr = root->elements[0]->mbr;
    // Calculate the tree's MBR by repeatedly checking max and min value of container of previous MBRs and current MBR
    if (isInit)  // only for 1st level since traversal is recursive
    {
        for (int i = 1; i < root->count; i++)
        {
            mbr = createMBR(mbr, root->elements[i]->mbr);
        }
        printf("Tree MBR: (%d, %d) -> (%d, %d)", mbr.bottomLeft.x, mbr.bottomLeft.y, mbr.topRight.x, mbr.topRight.y);
    }

    if (root->is_leaf)
        printf("\nLeaf Node: ");
    else if (root->parent == NULL)
        printf("\nRoot Node: ");
    else
        printf("\nInternal Node: ");

    // iterating through all elements of the root
    for (int i = 0; i < root->count; i++)
    {
        Rect rect = root->elements[i]->mbr;
        // Leaf node condition
        if (root->is_leaf)
        {
            if (rect.topRight.x == rect.bottomLeft.x && rect.topRight.y == rect.bottomLeft.y)
            {
                printf("(%d, %d)", rect.topRight.x, rect.topRight.y);
            }
            else
            {
                printf("(%d, %d) -> (%d, %d)", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
            }
        }
        // Root node condition
        else if (root->parent == NULL)
        {
            printf("(%d, %d) -> (%d, %d)", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }
        // Internal node condition
        else
        {
            printf("(%d, %d) -> (%d, %d)", rect.bottomLeft.x, rect.bottomLeft.y, rect.topRight.x, rect.topRight.y);
        }
        if (i < root->count - 1) printf(", ");
    }

    // traverse through all the children of current node
    for (int i = 0; i < root->count; i++)
    {
        if (!root->is_leaf) traversal(root->elements[i]->child, false);
    }
    if (isInit) printf("\n");
}

/* -----------------MAIN FUNCTION--------------------------------------------------------- */

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
