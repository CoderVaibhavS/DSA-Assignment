#include "rtree.h"
#include <math.h>
#include <stdlib.h>

// node1 and 2 are the splitted nodes, after splitting free(node)
void pickSeeds(Node* node, Node* node1, Node* node2) {
    int max_area = 0, area, area1, area2;       // distance b/w points
    Rect rect, rect1, rect2;

    for(int i=0; i<node->count; i++) {
        for(int j=i+1; j<node->count; j++) {

            rect1 = node->elements[i]->mbr;
            rect2 = node->elements[j]->mbr;

            rect = createMBR(rect1, rect2);

            area = calculateAreaOfRectangle(rect);
            area1 = calculateAreaOfRectangle(rect1);
            area2 = calculateAreaOfRectangle(rect2);

            if (max_area < area - area1 - area2)
            {   // we are selecting the 2 rectangles which have the maximum area
                // inbetween them when we bound those two rectangles with a
                // bigger rectangle
                max_area = area - area1 - area2;
                node1->elements[0] = node->elements[i];
                node2->elements[0] = node->elements[j];
            }
        }
    }
    node1->count = 1;
    node2->count = 1;
}

bool isPresent(Node_ele **ele, int size, Rect r) {
    Rect mbr;
    for(int i=0; i<size; i++) {
        mbr = ele[i]->mbr;
        if(mbr.bottomLeft.x == r.bottomLeft.x && mbr.bottomLeft.y == r.bottomLeft.y && mbr.topRight.x == r.topRight.x && mbr.topRight.y == r.topRight.y)
            return true;
    }
    return false;
}

void pickNext(Node *node, Node *node1, Node *node2) {
    int max_diff = 0, diff, diff1, diff2, idx;
    int d1, d2;
    for(int i=0; i<node->count; i++) {
        if(!isPresent(node1->elements, node1->count, node->elements[i]->mbr) && !isPresent(node2->elements, node2->count, node->elements[i]->mbr)) {
            d1 = calcAreaEnlargement(node1->parent->mbr, node->elements[i]->mbr);
            d2 = calcAreaEnlargement(node2->parent->mbr, node->elements[i]->mbr);
            diff = fabs(d1-d2);
            if(max_diff <= diff) {
                max_diff = diff;
                diff1 = d1;
                diff2 = d2;
                idx = i;
            }
        }
    }

    if(diff1 < diff2) {
        node1->elements[node->count++] = node->elements[idx];
    }
    else {
        node2->elements[node->count++] = node->elements[idx];
    }
}

void nodeSplit(Node *node) {
    // UPDATE THE NODE PARENTS
    Node *node1 = createNode(node->parent);
    Node *node2 = createNode(node->parent);

    pickSeeds(node, node1, node2);

    while(node1->count + node2->count < node->count) {
        // node2 is underflowed
        if(MAX_ENTRIES + 1 - node1->count == MIN_ENTRIES) {
            for(int i=0; i<node->count; i++) {
                if(!isPresent(node1->elements, node1->count, node->elements[i]->mbr) && !isPresent(node2->elements, node2->count, node->elements[i]->mbr)) {
                node2->elements[node2->count++] = node->elements[i];
                }
            }
        }
        // node1 is underflowed
        else if(MAX_ENTRIES + 1 - node2->count == MIN_ENTRIES) {
            for(int i=0; i<node->count; i++) {
                if(!isPresent(node1->elements, node1->count, node->elements[i]->mbr) && !isPresent(node2->elements, node2->count, node->elements[i]->mbr)) {
                node1->elements[node1->count++] = node->elements[i];
                }
            }
        }
        else {
            pickNext(node, node1, node2);
        }
    }
    free(node);
}