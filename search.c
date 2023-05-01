#include <stdlib.h>

#include "rtree.h"

bool is_overlap(Rect r, Rect mbr)  // checks for an overlap between the
                                   // rectangle and the MBR in a node
{
    if (r.bottomLeft.x <= mbr.topRight.x && r.bottomLeft.y <= mbr.topRight.y && r.topRight.x >= mbr.bottomLeft.x &&
        r.topRight.y >= mbr.bottomLeft.y)
        return true;
    // returns true if the bottomleft point of search rectangle is less than the
    // topright of MBR and the topright of search rectangle is greater than
    // the bottom left of MBR
    return false;
}

void search(Node *search_node,
            Rect search_rect)  // node of rtree and rectangle to be searched are
                               // passed as parameters to the search function
{
    for (int i = 0; i < search_node->count; i++)  // iterates over the MBRs present in the passed node
    {
        if (&search_node->elements[i] != NULL &&
            is_overlap(search_rect,
                       search_node->elements[i]->mbr))  // checks for an overlap through
                                                        // the is_overlap function
        {
            if (search_node->parent == NULL)  // overlapped MBR is from a root node
            {
                printf("%s overlapped MBR index : %d, BottomLeft & TopRight bounds : (%d,%d) (%d,%d) \n",
                       "\nRoot node - ", i + 1, search_node->elements[i]->mbr.bottomLeft.x,
                       search_node->elements[i]->mbr.bottomLeft.y, search_node->elements[i]->mbr.topRight.x,
                       search_node->elements[i]->mbr.topRight.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }
            else if (search_node->is_leaf == false)  // overlapped MBR is from an internal node
            {
                printf("%s overlapped MBR index : %d, BottomLeft & TopRight bounds : (%d,%d) (%d,%d) \n",
                       " --> internal node - ", i + 1, search_node->elements[i]->mbr.bottomLeft.x,
                       search_node->elements[i]->mbr.bottomLeft.y, search_node->elements[i]->mbr.topRight.x,
                       search_node->elements[i]->mbr.topRight.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }
            else  // overlapped MBR is part of a leaf node (datapoint)
            {
                printf(" %s overlapped datapoint index : %d, datapoint : (%d,%d) \n", "   ----> leaf node - ", i + 1,
                       search_node->elements[i]->mbr.bottomLeft.x, search_node->elements[i]->mbr.bottomLeft.y);
                // if an overlap is found, the bottomleft and topright datapoints of
                // the MBR is displayed along with the type of node the MBR is a part of
            }

            if (search_node->elements[i]->child != NULL && search_node->is_leaf == false)
                search(search_node->elements[i]->child, search_rect);
            // if the passed node is a non-leaf node, then we first descent
            // into the r-tree before searching in the MBRs at same level,
            // passing the corresponding child of overlapping MBR as the
            // root node of the subtree.

            else  // if the passed node is a leaf node, we search the MBRs
                  // present in this leaf node for a possible overlap
                continue;
        }
    }
    return;
}

// functions and code of testing.c used to test the search operation,
// CHANGES MADE :
// tweaked with the CreateNode logic to change parent node's is_leaf to false
// added 1 child node to get an internal node,
//----- final structure being : 1 root node at level 1,
//---------------------------   1 internal node at level 2,
//---------------------------   3 leaf nodes at level 2 & 1 leaf node at level 3

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Node_ele *createNodeEle(Node *container, Point topRight, Point bottomLeft)
// {
//     Node_ele *node_ele = (Node_ele *)malloc(sizeof(Node_ele));
//     node_ele->container = container;
//     node_ele->child = NULL;
//     node_ele->mbr.bottomLeft = bottomLeft;
//     node_ele->mbr.topRight = topRight;

//     return node_ele;
// }

// // Creating Node function

// Node *createNode(Node_ele *parent)
// {
//     Node *node = (Node *)malloc(sizeof(Node));  // creating a node dynamically

//     node->is_leaf = true;  // initializing all the fiels of the struct node.
//     node->count = 0;       // initial count=0
//     node->elements = (Node_ele **)malloc((MIN_ENTRIES) * sizeof(Node_ele *));  // initially no elements in the node
//     node->parent = parent;                                                     // initializing parent
//     if (parent != NULL) node->parent->container->is_leaf = false; // added this tweak

//     return node;  // returning the node
// }

// // creating R Tree function
// Rtree *createRtree()  // No parameters required to create a rtree
// {
//     Rtree *rtree = (Rtree *)malloc(sizeof(Rtree));  // Creating r tree dynamically
//     rtree->root = createNode(NULL);                 // Only node is the root itself,hence it's a leaf node.

//     return rtree;  // returning the tree
// }

// /* ----------------------------------------------PREORDER
// TRAVERSAL----------------------------------------------------
//  */
// void traversal(Node *root)
// {
//     if (root == NULL) return;

//     for (int i = 0; i < root->count; i++)
//     {
//         Rect rect = root->elements[i]->mbr;
//         if (root->elements[i]->container->parent == NULL)
//         {
//             printf("Root Node Element: ");
//             printf("%d %d %d %d\n", rect.topRight.x, rect.topRight.y, rect.bottomLeft.x, rect.bottomLeft.y);
//         }
//         else if (root->elements[i]->container->is_leaf)
//         {
//             printf("Leaf Node Element: ");
//             printf("%d %d\n", rect.topRight.x, rect.topRight.y);
//         }
//         else
//         {
//             printf("Internal Node Element: ");
//             printf("%d %d %d %d\n", rect.topRight.x, rect.topRight.y, rect.bottomLeft.x, rect.bottomLeft.y);
//         }
//         if (!root->is_leaf) traversal(root->elements[i]->child);
//     }
// }
// //--------------------------------------------------------------------------------------------------------------------------------------

// int main()
// {
//     Rtree *rtree = createRtree();

//     rtree->root = createNode(NULL);
//     rtree->root->is_leaf = false;

//     rtree->root->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         rtree->root->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     Point topRight, bottomLeft;
//     topRight.x = topRight.y = 100;
//     bottomLeft.x = bottomLeft.y = 75;
//     rtree->root->elements[0] = createNodeEle(rtree->root, topRight, bottomLeft);
//     rtree->root->count++;

//     topRight.x = topRight.y = 75;
//     bottomLeft.x = bottomLeft.y = 50;
//     rtree->root->elements[1] = createNodeEle(rtree->root, topRight, bottomLeft);
//     rtree->root->count++;

//     topRight.x = topRight.y = 50;
//     bottomLeft.x = bottomLeft.y = 25;
//     rtree->root->elements[2] = createNodeEle(rtree->root, topRight, bottomLeft);
//     rtree->root->count++;

//     topRight.x = topRight.y = 25;
//     bottomLeft.x = bottomLeft.y = 0;
//     rtree->root->elements[3] = createNodeEle(rtree->root, topRight, bottomLeft);
//     rtree->root->count++;

//     Node *temp;

//     /* -----------------------------------------CHILD 1---------------------------------------- */
//     rtree->root->elements[0]->child = createNode(rtree->root->elements[0]);
//     temp = rtree->root->elements[0]->child;

//     temp->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         temp->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     topRight.x = topRight.y = 95;
//     bottomLeft.x = bottomLeft.y = 75;
//     temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 90;
//     bottomLeft.x = bottomLeft.y = 75;
//     temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 85;
//     bottomLeft.x = bottomLeft.y = 75;
//     temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 80;
//     bottomLeft.x = bottomLeft.y = 75;
//     temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     /* -----------------------------------------CHILD 2---------------------------------------- */

//     rtree->root->elements[1]->child = createNode(rtree->root->elements[1]);
//     temp = rtree->root->elements[1]->child;

//     temp->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         temp->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     topRight.x = topRight.y = 70;
//     bottomLeft.x = bottomLeft.y = 50;
//     temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 65;
//     bottomLeft.x = bottomLeft.y = 50;
//     temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 60;
//     bottomLeft.x = bottomLeft.y = 50;
//     temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 55;
//     bottomLeft.x = bottomLeft.y = 50;
//     temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//   // -------- added a child at level 3 to make one internal node,
//   // -------- final structure being : 1 root node at level 1,
//   // ------------------------------   1 internal node at level 2,
//   // ------------------------------   3 leaf nodes at level 2 & 1 leaf node at level 3

//     temp->elements[2]->child = createNode(temp->elements[2]);
//     temp = temp->elements[2]->child;

//     temp->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         temp->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     topRight.x = topRight.y = 58;
//     bottomLeft.x = bottomLeft.y = 51;
//     temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     /* -----------------------------------------CHILD 3---------------------------------------- */

//     rtree->root->elements[2]->child = createNode(rtree->root->elements[2]);
//     temp = rtree->root->elements[2]->child;

//     temp->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         temp->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     topRight.x = topRight.y = 45;
//     bottomLeft.x = bottomLeft.y = 25;
//     temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 40;
//     bottomLeft.x = bottomLeft.y = 25;
//     temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 35;
//     bottomLeft.x = bottomLeft.y = 25;
//     temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 30;
//     bottomLeft.x = bottomLeft.y = 25;
//     temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     /* -----------------------------------------CHILD 4---------------------------------------- */

//     rtree->root->elements[3]->child = createNode(rtree->root->elements[3]);
//     temp = rtree->root->elements[3]->child;

//     temp->elements = (Node_ele **)malloc(MAX_ENTRIES * sizeof(Node_ele *));
//     for (int i = 0; i < MAX_ENTRIES; i++)
//     {
//         temp->elements[i] = (Node_ele *)malloc(sizeof(Node_ele));
//     }

//     topRight.x = topRight.y = 20;
//     bottomLeft.x = bottomLeft.y = 0;
//     temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 15;
//     bottomLeft.x = bottomLeft.y = 0;
//     temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 10;
//     bottomLeft.x = bottomLeft.y = 0;
//     temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     topRight.x = topRight.y = 5;
//     bottomLeft.x = bottomLeft.y = 0;
//     temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
//     temp->count++;

//     // traversal(rtree->root);
//     // Rect r1;
//     // r1.bottomLeft.x = 0;
//     // r1.bottomLeft.y = 0;
//     // r1.topRight.x = 5;
//     // r1.topRight.y = 5;
//     // ChooseLeaf(rtree, r1);
//     Rect r1 = create_rectangle(40, 40, 65, 65);
//     search(rtree->root, r1);
// }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
