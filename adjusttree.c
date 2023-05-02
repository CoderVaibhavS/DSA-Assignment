#include <stdio.h>

#include "rtree.h"

/* ----------------------------------------ADJUST TREE--------------------------------------------- */

SplitResult *adjustTree(SplitResult *split)
{
    SplitResult *splitOp = split;    // splitOp assigned to split(which was passed as parameter) and
    Node *nodeOp1 = splitOp->leaf1;  // similarly nodeOp1,nodeOp2 and parentOp assigned to the leaf nodes leaf1
    Node *nodeOp2 = splitOp->leaf2;  // leaf2 and parent which are the parameters of the SplitResult structure.
    Node_ele *parentOp = splitOp->parent;

    while (parentOp != NULL)  // when node_ele (operating parent) is not null
    {
        createNodeParent(nodeOp1);  // assign parent to nodeOp1
        if (nodeOp1 != nodeOp2)     // when there are 2 operating nodes and not just a single operating node
        {
            createNodeParent(nodeOp2);  // assign parrent to nodeOp2 also
        }

        updateParent(parentOp, nodeOp1,
                     nodeOp2);  // Update nodeOp1's and nodeOp2's parent MBRs in container of parent MBR

        parentOp = nodeOp1->parent;  // nodeOp1's parent point to the operating parent parentOp

        if (parentOp->container->count > MAX_ENTRIES)  // operating parent(parentOp) node split case
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
        splitOp = (SplitResult *)malloc(sizeof(SplitResult));
        splitOp->parent = parentOp;
        splitOp->leaf1 = nodeOp1;
        splitOp->leaf2 = nodeOp2;
    }

    return splitOp;
}
