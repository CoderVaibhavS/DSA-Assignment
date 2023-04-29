#include <stdio.h>

#include "rtree.h"

void updateParent(Node_ele *parent, Node *node1, Node *node2)
{
    Node *parentNode = parent->container;
    int ele;
    for (int i = 0; i < parentNode->count; i++)
    {
        if (parentNode->elements[i] == parent)
        {
            ele = i;
            break;
        }
    }
    parentNode->elements[ele] = node1->parent;
    node1->parent->container = parentNode;
    if (node1 != node2)
    {
        parentNode->elements[parentNode->count++] = node2->parent;
        node2->parent->container = parentNode;
    }
}

SplitResult *adjustTree(SplitResult *split)
{
    SplitResult *splitOp = split;
    Node *nodeOp1 = splitOp->leaf1;
    Node *nodeOp2 = splitOp->leaf2;
    Node_ele *parent = splitOp->parent;
    while (parent != NULL)
    {
        createNodeParent(nodeOp1);
        if (nodeOp1 != nodeOp2)
        {
            createNodeParent(nodeOp2);
        }
        updateParent(parent, nodeOp1, nodeOp2);
        if (parent->container->count > MAX_ENTRIES)
        {
            if (splitOp != NULL) free(splitOp);
            splitOp = nodeSplit(parent->container);
            nodeOp1 = splitOp->leaf1;
            nodeOp2 = splitOp->leaf2;
            parent = splitOp->parent;
        }
        else
        {
            if (splitOp != NULL) free(splitOp);
            splitOp = NULL;
            nodeOp1 = parent->container;
            nodeOp2 = nodeOp1;
            parent = nodeOp1->parent;
        }
    }
    if (splitOp == NULL)
    {
        splitOp = (SplitResult *)malloc(sizeof(SplitResult));
        splitOp->parent = parent;
        splitOp->leaf1 = nodeOp1;
        splitOp->leaf2 = nodeOp2;
    }
    return splitOp;
}
