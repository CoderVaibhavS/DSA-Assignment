#include <stdio.h>

#include "rtree.h"

// Insert function incorporatind all other files
void insert(Rtree* tree, Point bottomLeft, Point topRight)
{
    Rect mbr = {topRight, bottomLeft};
    // choose leaf based on elem
    Node* leaf = ChooseLeaf(tree, mbr);
    leaf->elements[leaf->count++] =
        createNodeEle(leaf, topRight, bottomLeft);  // create node_ele for element to be added
    SplitResult* split = NULL;

    if (leaf->count > MAX_ENTRIES)  // node overflowed -> node requires splitting
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
        NodeEle* dummy = createNodeEle(root, topRight, bottomLeft);
        root->elements[root->count++] = dummy;
        updateParent(dummy, split->leaf1, split->leaf2);
        tree->root = root;
    }
}
