#include "rtree.h"
#include <math.h>
#include <stdlib.h>

void pickSeeds(Node* node, Node* node1, Node* node2) {
    int max_area = 0, area, area1, area2;       // distance b/w points
    Rect rect, rect1, rect2;

    node1 = createNode(node->parent, true);
    node2 = createNode(node->parent, true);

    for(int i=0; i<node->count; i++) {
        for(int j=i+1; j<node->count; j++) {

            rect1 = node->elements[i].mbr;
            rect2 = node->elements[j].mbr;

            rect.topRight.x =
                fmax(rect1.topRight.x,
                     rect2.topRight
                         .x);  // we are doing this to find the rectangle of
                               // smallest area that encloses rect1 and rect2
            rect.topRight.y = fmax(rect1.topRight.y, rect2.topRight.y);
            rect.bottomLeft.x = fmin(rect1.bottomLeft.x, rect2.bottomLeft.x);
            rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);

            area = calculateAreaOfRectangle(rect);
            area1 = calculateAreaOfRectangle(rect1);
            area2 = calculateAreaOfRectangle(rect2);

            if (max_area < area - area1 - area2)
            {  // we are selecting the 2 rectangles which have the maximum aread
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

bool isPresent(Node_ele *ele, int size, Rect r) {
    Rect mbr;
    for(int i=0; i<size; i++) {
        mbr = ele[i].mbr;
        if(mbr.bottomLeft.x == r.bottomLeft.x && mbr.bottomLeft.y == r.bottomLeft.y && mbr.topRight.x == r.topRight.x && mbr.topRight.y == r.topRight.y)
            return true;
    }
    return false;
}

// void pickNext(Node *node, Node *node1, Node *node2) {
//     int area_inc = 0, max_diff = 0, diff1, diff2;
//     Rect r1, r2;
//     for(int i=0; i<node->count; i++) {
//         if(!isPresent(node1->elements, node1->count, node->elements[i].mbr) && !isPresent(node2->elements, node2->count, node->elements[i].mbr)) {
//             if(MAX_ENTRIES - node1->count == MIN_ENTRIES) {
//                 node2->elements[node2->count++] = node->elements[i];
//             }
//             else if(MAX_ENTRIES - node2->count == MIN_ENTRIES) {
//                 node1->elements[node1->count++] = node->elements[i];
//             }
//             else {
                
//             }
//         }
//     }
// }