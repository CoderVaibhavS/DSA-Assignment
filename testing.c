#include <stdlib.h>
#include <stdbool.h>

#include "rtree.h"

int main()
{
    Rtree* rtree = createRtree();
    
    rtree->root = createNode(NULL);
    rtree->root->is_leaf = false;

    rtree->root->elements = (Node_ele**)malloc(MAX_ENTRIES * sizeof(Node_ele*));
    for(int i=0; i<MAX_ENTRIES; i++) {
        rtree->root->elements[i] = (Node_ele *) malloc(sizeof(Node_ele));
    }

    Point topRight, bottomLeft;
    topRight.x = topRight.y = 100;
    bottomLeft.x = bottomLeft.y = 75;
    rtree->root->elements[0] = createNodeEle(rtree->root, topRight, bottomLeft);
    rtree->root->count++;

    topRight.x = topRight.y = 75;
    bottomLeft.x = bottomLeft.y = 50;
    rtree->root->elements[1] = createNodeEle(rtree->root, topRight, bottomLeft);
    rtree->root->count++;

    topRight.x = topRight.y = 50;
    bottomLeft.x = bottomLeft.y = 25;
    rtree->root->elements[2] = createNodeEle(rtree->root, topRight, bottomLeft);
    rtree->root->count++;

    topRight.x = topRight.y = 25;
    bottomLeft.x = bottomLeft.y = 0;
    rtree->root->elements[3] = createNodeEle(rtree->root, topRight, bottomLeft);
    rtree->root->count++;

    Node* temp;

    /* -----------------------------------------CHILD 1---------------------------------------- */
    rtree->root->elements[0]->child = createNode(rtree->root->elements[0]);
    temp = rtree->root->elements[0]->child;

    temp->elements = (Node_ele**)malloc(MAX_ENTRIES * sizeof(Node_ele*));
    for(int i=0; i<MAX_ENTRIES; i++) {
        temp->elements[i] = (Node_ele *) malloc(sizeof(Node_ele));
    }

    topRight.x = topRight.y = 95;
    bottomLeft.x = bottomLeft.y = 75;
    temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 90;
    bottomLeft.x = bottomLeft.y = 75;
    temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 85;
    bottomLeft.x = bottomLeft.y = 75;
    temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 80;
    bottomLeft.x = bottomLeft.y = 75;
    temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    /* -----------------------------------------CHILD 2---------------------------------------- */

    rtree->root->elements[1]->child = createNode(rtree->root->elements[1]);
    temp = rtree->root->elements[1]->child;

    temp->elements = (Node_ele**)malloc(MAX_ENTRIES * sizeof(Node_ele*));
    for(int i=0; i<MAX_ENTRIES; i++) {
        temp->elements[i] = (Node_ele *) malloc(sizeof(Node_ele));
    }

    topRight.x = topRight.y = 70;
    bottomLeft.x = bottomLeft.y = 50;
    temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 65;
    bottomLeft.x = bottomLeft.y = 50;
    temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 60;
    bottomLeft.x = bottomLeft.y = 50;
    temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 55;
    bottomLeft.x = bottomLeft.y = 50;
    temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    /* -----------------------------------------CHILD 3---------------------------------------- */

    rtree->root->elements[2]->child = createNode(rtree->root->elements[2]);
    temp = rtree->root->elements[2]->child;

    temp->elements = (Node_ele**)malloc(MAX_ENTRIES * sizeof(Node_ele*));
    for(int i=0; i<MAX_ENTRIES; i++) {
        temp->elements[i] = (Node_ele *) malloc(sizeof(Node_ele));
    }

    topRight.x = topRight.y = 45;
    bottomLeft.x = bottomLeft.y = 25;
    temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 40;
    bottomLeft.x = bottomLeft.y = 25;
    temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 35;
    bottomLeft.x = bottomLeft.y = 25;
    temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 30;
    bottomLeft.x = bottomLeft.y = 25;
    temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    /* -----------------------------------------CHILD 4---------------------------------------- */

    rtree->root->elements[3]->child = createNode(rtree->root->elements[3]);
    temp = rtree->root->elements[3]->child;

    temp->elements = (Node_ele**)malloc(MAX_ENTRIES * sizeof(Node_ele*));
    for(int i=0; i<MAX_ENTRIES; i++) {
        temp->elements[i] = (Node_ele *) malloc(sizeof(Node_ele));
    }

    topRight.x = topRight.y = 20;
    bottomLeft.x = bottomLeft.y = 0;
    temp->elements[0] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 15;
    bottomLeft.x = bottomLeft.y = 0;
    temp->elements[1] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 10;
    bottomLeft.x = bottomLeft.y = 0;
    temp->elements[2] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    topRight.x = topRight.y = 5;
    bottomLeft.x = bottomLeft.y = 0;
    temp->elements[3] = createNodeEle(temp, topRight, bottomLeft);
    temp->count++;

    traversal(rtree->root);
}
