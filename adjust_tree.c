#include <stdio.h>

#include "rtree.h"

/* ----------------------------------------ADJUST TREE--------------------------------------------- */

// adjustTree function to propagate changes up in subtree
// leaf1 == leaf2 of split is condition if node did not split
SplitResult *adjustTree(SplitResult *split)
{
    // Init local variables
    SplitResult *splitOp = split;
    Node *nodeOp1 = splitOp->leaf1;
    Node *nodeOp2 = splitOp->leaf2;
    NodeEle *parentOp = splitOp->parent;

    while (parentOp != NULL)  // Stop at root node
    {
        // Update parent nodes with apporpriate MBRs
        createNodeParent(nodeOp1);
        if (nodeOp1 != nodeOp2)
        {
            createNodeParent(nodeOp2);
        }
        updateParent(parentOp, nodeOp1, nodeOp2);
        parentOp = nodeOp1->parent;

        // Check if parent needs to be split
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
            splitOp = NULL;  // Assign splitOp to NULL if parent need not split
            nodeOp1 = parentOp->container;
            nodeOp2 = nodeOp1;
            parentOp = nodeOp1->parent;
        }
    }

    if (splitOp == NULL)  // Check if root did not split
    {
        splitOp = (SplitResult *)malloc(sizeof(SplitResult));
        splitOp->parent = parentOp;
        splitOp->leaf1 = nodeOp1;
        splitOp->leaf2 = nodeOp2;
    }

    return splitOp;
}
