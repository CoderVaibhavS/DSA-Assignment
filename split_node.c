#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rtree.h"

// node1 and 2 are the splitted nodes, after splitting free(node)
void pickSeeds(Node *node, Node *node1, Node *node2)
{
    int max_area, area, area1, area2;  // distance b/w points
    int elem1, elem2;
    Rect rect, rect1, rect2;
    rect1 = node->elements[0]->mbr;
    rect2 = node->elements[1]->mbr;

    rect = createMBR(rect1, rect2);

    area = calculateAreaOfRectangle(rect);
    area1 = calculateAreaOfRectangle(rect1);
    area2 = calculateAreaOfRectangle(rect2);
    max_area = area - area1 - area2;
    elem1 = 0;
    elem2 = 1;

    for (int i = 0; i < node->count; i++)
    {
        for (int j = i + 1; j < node->count; j++)
        {
            rect1 = node->elements[i]->mbr;
            rect2 = node->elements[j]->mbr;

            rect = createMBR(rect1, rect2);

            area = calculateAreaOfRectangle(rect);
            area1 = calculateAreaOfRectangle(rect1);
            area2 = calculateAreaOfRectangle(rect2);

            if (max_area < area - area1 - area2)
            {  // we are selecting the 2 rectangles which have the maximum area
                // inbetween them when we bound those two rectangles with a
                // bigger rectangle
                max_area = area - area1 - area2;
                elem1 = i;
                elem2 = j;
            }
        }
    }
    node1->elements[0] = node->elements[elem1];
    node2->elements[0] = node->elements[elem2];
    node->elements[elem1]->container = node1;
    node->elements[elem2]->container = node2;
    node1->count = 1;
    node2->count = 1;
}

bool isPresent(Node_ele **ele, int size, Rect r)
{
    Rect mbr;
    for (int i = 0; i < size; i++)
    {
        mbr = ele[i]->mbr;
        if (mbr.bottomLeft.x == r.bottomLeft.x && mbr.bottomLeft.y == r.bottomLeft.y &&
            mbr.topRight.x == r.topRight.x && mbr.topRight.y == r.topRight.y)
            return true;
    }
    return false;
}

void pickNext(Node *node, Node *node1, Node *node2)
{
    int max_diff = 0, diff, diff1, diff2, idx;
    int d1, d2, area1, area2;
    for (int i = 0; i < node->count; i++)
    {
        if (!isPresent(node1->elements, node1->count, node->elements[i]->mbr) &&
            !isPresent(node2->elements, node2->count, node->elements[i]->mbr))
        {
            d1 = calcAreaEnlargement(node1->parent->mbr, node->elements[i]->mbr);
            d2 = calcAreaEnlargement(node2->parent->mbr, node->elements[i]->mbr);
            diff = abs(d1 - d2);
            if (max_diff <= diff)
            {
                area1 = calculateAreaOfRectangle(node1->parent->mbr);
                area2 = calculateAreaOfRectangle(node2->parent->mbr);
                max_diff = diff;
                diff1 = d1;
                diff2 = d2;
                idx = i;
            }
        }
    }

    if (diff1 < diff2)
    {
        node1->elements[node1->count++] = node->elements[idx];
        node->elements[idx]->container = node1;
    }
    else if (diff2 > diff1)
    {
        node2->elements[node2->count++] = node->elements[idx];
        node->elements[idx]->container = node2;
    }
    else if (area1 > area2)
    {
        node2->elements[node2->count++] = node->elements[idx];
        node->elements[idx]->container = node2;
    }
    else if (area2 > area1)
    {
        node1->elements[node1->count++] = node->elements[idx];
        node->elements[idx]->container = node1;
    }
    else if (node1->count > node2->count)
    {
        node2->elements[node2->count++] = node->elements[idx];
        node->elements[idx]->container = node2;
    }
    else
    {
        node1->elements[node1->count++] = node->elements[idx];
        node->elements[idx]->container = node1;
    }
}

SplitResult *nodeSplit(Node *node)
{
    // UPDATE THE NODE PARENTS
    Node *node1 = createNode(NULL, node->is_leaf);
    Node *node2 = createNode(NULL, node->is_leaf);

    pickSeeds(node, node1, node2);

    while (node1->count + node2->count < node->count)
    {
        createNodeParent(node1);
        createNodeParent(node2);
        // node2 is underflowed
        if (MAX_ENTRIES + 1 - node1->count == MIN_ENTRIES)
        {
            for (int i = 0; i < node->count; i++)
            {
                if (!isPresent(node1->elements, node1->count, node->elements[i]->mbr) &&
                    !isPresent(node2->elements, node2->count, node->elements[i]->mbr))
                {
                    node2->elements[node2->count++] = node->elements[i];
                    node->elements[i]->container = node2;
                }
            }
        }
        // node1 is underflowed
        else if (MAX_ENTRIES + 1 - node2->count == MIN_ENTRIES)
        {
            for (int i = 0; i < node->count; i++)
            {
                if (!isPresent(node1->elements, node1->count, node->elements[i]->mbr) &&
                    !isPresent(node2->elements, node2->count, node->elements[i]->mbr))
                {
                    node1->elements[node1->count++] = node->elements[i];
                    node->elements[i]->container = node1;
                }
            }
        }
        else
        {
            pickNext(node, node1, node2);
        }
    }
    Node_ele *parent = node->parent;
    free(node);
    SplitResult *split = (SplitResult *)malloc(sizeof(SplitResult));
    split->parent = parent;
    split->leaf1 = node1;
    split->leaf2 = node2;
    return split;
}
