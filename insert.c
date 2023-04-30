#include <stdio.h>

#include "rtree.h"

void insert(Rtree* tree, Point bottomLeft, Point topRight)
{
    Rect mbr = {topRight, bottomLeft};
    Node* leaf = ChooseLeaf(tree, mbr);  // choose leaf based on elem
    leaf->elements[leaf->count++] = createNodeEle(leaf, topRight, bottomLeft);
    SplitResult* split = NULL;

    if (leaf->count > MAX_ENTRIES)
    {
        split = nodeSplit(leaf);
    }
    else
    {
        split = (SplitResult*)malloc(sizeof(SplitResult));
        split->parent = leaf->parent;
        split->leaf1 = leaf;
        split->leaf2 = leaf;
    }

    split = adjustTree(split);
    if (split->leaf1 != split->leaf2)
    {
        Node* root = createNode(NULL, false);
        createNodeParent(split->leaf1);
        createNodeParent(split->leaf2);
        Node_ele* dummy = createNodeEle(root, topRight, bottomLeft);
        root->elements[root->count++] = dummy;
        updateParent(dummy, split->leaf1, split->leaf2);
        tree->root = root;
    }
}
