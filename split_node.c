#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rtree.h"

// node1 and 2 are the splitted nodes, choose first elements to be inserted in both of them
// using pickseed function

void pickSeeds(Node *node, Node *node1, Node *node2)
{
    int max_area, area, area1, area2;
    int elem1, elem2;
    Rect rect, rect1, rect2;
    rect1 = node->elements[0]->mbr;  // MBR of 1st node_ele and 2nd node_ele are considered first
    rect2 = node->elements[1]->mbr;

    rect = createMBR(rect1, rect2);  // MBR of the above two considered rect1 and rect2

    area = calculateAreaOfRectangle(rect);  // calculating the area of rect,rect1 and rect2
    area1 = calculateAreaOfRectangle(rect1);
    area2 = calculateAreaOfRectangle(rect2);
    max_area = area - area1 - area2;
    elem1 = 0;
    elem2 = 1;

    // traverse every possible pair of node elements
    for (int i = 0; i < node->count; i++)
    {
        for (int j = i + 1; j < node->count; j++)
        {
            rect1 = node->elements[i]->mbr;
            rect2 = node->elements[j]->mbr;

            rect = createMBR(rect1, rect2);  // MBR bounding 2 rects

            area = calculateAreaOfRectangle(rect);
            area1 = calculateAreaOfRectangle(rect1);
            area2 = calculateAreaOfRectangle(rect2);

            // calculating the most wasteful area -> insert both rectangles in separate nodes
            if (max_area < area - area1 - area2)
            {
                // maximizing area-area1-area2 to basically get the farthest two objects
                // to consider while picking the seeds into two different nodes

                max_area = area - area1 - area2;
                elem1 = i;  // storing the values of elem1 ad elem2
                elem2 = j;
            }
        }
    }

    node1->elements[0] = node->elements[elem1];  // assigning the elements of node1 and node2
    node2->elements[0] = node->elements[elem2];  // using the previously found values of elem1 and elem2
    node->elements[elem1]->container = node1;    // now these new node_ele are assigned their container nodes.
    node->elements[elem2]->container = node2;
    node1->count = 1;  // increasing count of the nodes by 1
    node2->count = 1;
}

// identify the presence of a rectangle in a node
bool isPresent(Node_ele **ele, int size, Node_ele *searchElem)
{
    Rect mbr;
    for (int i = 0; i < size; i++)
    {
        mbr = ele[i]->mbr;
        if (ele[i] == searchElem) return true;
    }
    return false;
}

// choose the node where a rect can be inserted after picking initial seeds
void pickNext(Node *node, Node *node1, Node *node2)
{
    int max_diff = 0, diff, diff1, diff2, idx;  // defining and initializing variables
    int d1, d2;
    int area1 = calculateAreaOfRectangle(node1->parent->mbr);
    int area2 = calculateAreaOfRectangle(node2->parent->mbr);
    bool setFlag = false;

    for (int i = 0; i < node->count; i++)
    {
        // checking if elements in the node are already present or not using the isPresent function

        if (!isPresent(node1->elements, node1->count, node->elements[i]) &&
            !isPresent(node2->elements, node2->count, node->elements[i]))
        {
            // calculate enlargements in both nodes MBR for each rectangle that is not alloted to a node
            d1 = calcAreaEnlargement(node1->parent->mbr, node->elements[i]->mbr);
            d2 = calcAreaEnlargement(node2->parent->mbr, node->elements[i]->mbr);
            diff = abs(d1 - d2);

            // prioritise the rectangle with max diff in enlargements
            if (setFlag == false || max_diff <= diff)
            {
                max_diff = diff;
                diff1 = d1;
                diff2 = d2;
                idx = i;
                setFlag = true;
            }
        }
    }

    if (diff1 < diff2)  // allot to node1
    {
        node1->elements[node1->count++] = node->elements[idx];
        node->elements[idx]->container = node1;
    }
    else if (diff1 > diff2)  // allot to node2
    {
        node2->elements[node2->count++] = node->elements[idx];
        node->elements[idx]->container = node2;
    }
    // if diff is same, allot to node with the MBR having smaller area
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
    // if area is also same, then allot to the node with less no of elements
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

// main split function
SplitResult *nodeSplit(Node *node)
{
    // two splitted nodes
    Node *node1 = createNode(NULL, node->is_leaf);
    Node *node2 = createNode(NULL, node->is_leaf);

    pickSeeds(node, node1, node2);

    while (node1->count + node2->count < node->count)
    {
        createNodeParent(node1);
        createNodeParent(node2);

        if (MAX_ENTRIES + 1 - node1->count == MIN_ENTRIES)  // node2 is underflowed
        {
            for (int i = 0; i < node->count; i++)
            {
                if (!isPresent(node1->elements, node1->count, node->elements[i]) &&
                    !isPresent(node2->elements, node2->count, node->elements[i]))
                {
                    node2->elements[node2->count++] = node->elements[i];
                    node->elements[i]->container = node2;
                }
            }
        }
        else if (MAX_ENTRIES + 1 - node2->count == MIN_ENTRIES)  // node1 is underflowed
        {
            for (int i = 0; i < node->count; i++)
            {
                if (!isPresent(node1->elements, node1->count, node->elements[i]) &&
                    !isPresent(node2->elements, node2->count, node->elements[i]))
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
