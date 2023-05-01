#include <stdio.h>
#include "rtree.h"

/* ----------------------------------------ADJUST TREE--------------------------------------------- */
SplitResult *adjustTree(SplitResult *split)
{
    SplitResult *splitOp = split;
    Node *nodeOp1 = splitOp->leaf1;
    Node *nodeOp2 = splitOp->leaf2;
    Node_ele *parentOp = splitOp->parent;

    while (parentOp != NULL)
    {
        createNodeParent(nodeOp1);
        if (nodeOp1 != nodeOp2)
        {
            createNodeParent(nodeOp2);
        }

        updateParent(parentOp, nodeOp1, nodeOp2);
        parentOp = nodeOp1->parent;

        if (parentOp->container->count > MAX_ENTRIES)
        {
            if (splitOp != NULL) free(splitOp);
            splitOp = nodeSplit(parentOp->container);
            nodeOp1 = splitOp->leaf1;
            nodeOp2 = splitOp->leaf2;
            parentOp = splitOp->parent;
        }
        else
        {
            if (splitOp != NULL) free(splitOp);
            splitOp = NULL;
            nodeOp1 = parentOp->container;
            nodeOp2 = nodeOp1;
            parentOp = nodeOp1->parent;
        }
    }

    if (splitOp == NULL)
    {
        splitOp = (SplitResult *) malloc(sizeof(SplitResult));
        splitOp->parent = parentOp;
        splitOp->leaf1 = nodeOp1;
        splitOp->leaf2 = nodeOp2;
    }

    return splitOp;
}
