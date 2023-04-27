#include <stdlib.h>
#include "rtree.h"

int main() {

    Rtree* rtree = (Rtree*) malloc(sizeof(Rtree));

    rtree->root = (Node*) malloc(sizeof(Node));
    rtree->root->count = 0;

    rtree->root->elements = (Node_ele*) malloc(MAX_ENTRIES*sizeof(Node_ele));
    rtree->root->elements[0].mbr.topRight.x = 100;
    rtree->root->elements[0].mbr.topRight.y = 100;
    rtree->root->elements[0].mbr.bottomLeft.x = 75;
    rtree->root->elements[0].mbr.bottomLeft.y = 75;
    rtree->root->count++;

    rtree->root->elements[1].mbr.topRight.x = 75;
    rtree->root->elements[1].mbr.topRight.y = 75;
    rtree->root->elements[1].mbr.bottomLeft.x = 50;
    rtree->root->elements[1].mbr.bottomLeft.y = 50;
    rtree->root->count++;

    rtree->root->elements[2].mbr.topRight.x = 50;
    rtree->root->elements[2].mbr.topRight.y = 50;
    rtree->root->elements[2].mbr.bottomLeft.x = 25;
    rtree->root->elements[2].mbr.bottomLeft.y = 25;
    rtree->root->count++;
    
    rtree->root->elements[3].mbr.topRight.x = 25;
    rtree->root->elements[3].mbr.topRight.y = 25;
    rtree->root->elements[3].mbr.bottomLeft.x = 0;
    rtree->root->elements[3].mbr.bottomLeft.y = 0;
    rtree->root->count++;

    Node* temp;

    /* -----------------------------------------CHILD 1---------------------------------------- */

    rtree->root->elements[0].child = (Node*) malloc(sizeof(Node));
    temp = rtree->root->elements[0].child;
    temp->count = 0;
    temp->elements = (Node_ele*) malloc(MAX_ENTRIES*sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 95;
    temp->elements[0].mbr.topRight.y = 95;
    temp->elements[0].mbr.bottomLeft.x = 75;
    temp->elements[0].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 90;
    temp->elements[1].mbr.topRight.y = 90;
    temp->elements[1].mbr.bottomLeft.x = 75;
    temp->elements[1].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 85;
    temp->elements[2].mbr.topRight.y = 85;
    temp->elements[2].mbr.bottomLeft.x = 75;
    temp->elements[2].mbr.bottomLeft.y = 75;
    temp->count++;

    rtree->root->elements[0].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 80;
    temp->elements[3].mbr.topRight.y = 80;
    temp->elements[3].mbr.bottomLeft.x = 75;
    temp->elements[3].mbr.bottomLeft.y = 75;
    temp->count++;

    /* -----------------------------------------CHILD 2---------------------------------------- */

    rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp = rtree->root->elements[1].child;
    temp->count = 0;
    temp->elements = (Node_ele*) malloc(MAX_ENTRIES*sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 70;
    temp->elements[0].mbr.topRight.y = 70;
    temp->elements[0].mbr.bottomLeft.x = 50;
    temp->elements[0].mbr.bottomLeft.y = 50;
    temp->count++;

    rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 65;
    temp->elements[1].mbr.topRight.y = 65;
    temp->elements[1].mbr.bottomLeft.x = 50;
    temp->elements[1].mbr.bottomLeft.y = 50;
    temp->count++;

    rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 60;
    temp->elements[2].mbr.topRight.y = 60;
    temp->elements[2].mbr.bottomLeft.x = 50;
    temp->elements[2].mbr.bottomLeft.y = 50;
    temp->count++;

    rtree->root->elements[1].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 55;
    temp->elements[3].mbr.topRight.y = 55;
    temp->elements[3].mbr.bottomLeft.x = 50;
    temp->elements[3].mbr.bottomLeft.y = 50;
    temp->count++;

    /* -----------------------------------------CHILD 3---------------------------------------- */

    rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp = rtree->root->elements[2].child;
    temp->count = 0;
    temp->elements = (Node_ele*) malloc(MAX_ENTRIES*sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 45;
    temp->elements[0].mbr.topRight.y = 45;
    temp->elements[0].mbr.bottomLeft.x = 25;
    temp->elements[0].mbr.bottomLeft.y = 25;
    temp->count++;

    rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 40;
    temp->elements[1].mbr.topRight.y = 40;
    temp->elements[1].mbr.bottomLeft.x = 25;
    temp->elements[1].mbr.bottomLeft.y = 25;
    temp->count++;

    rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 35;
    temp->elements[2].mbr.topRight.y = 35;
    temp->elements[2].mbr.bottomLeft.x = 25;
    temp->elements[2].mbr.bottomLeft.y = 25;
    temp->count++;

    rtree->root->elements[2].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 30;
    temp->elements[3].mbr.topRight.y = 30;
    temp->elements[3].mbr.bottomLeft.x = 25;
    temp->elements[3].mbr.bottomLeft.y = 25;
    temp->count++;

    /* -----------------------------------------CHILD 4---------------------------------------- */

    rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp = rtree->root->elements[3].child;
    temp->count = 0;
    temp->elements = (Node_ele*) malloc(MAX_ENTRIES*sizeof(Node_ele));
    temp->elements[0].mbr.topRight.x = 20;
    temp->elements[0].mbr.topRight.y = 20;
    temp->elements[0].mbr.bottomLeft.x = 0;
    temp->elements[0].mbr.bottomLeft.y = 0;
    temp->count++;

    rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[1].mbr.topRight.x = 15;
    temp->elements[1].mbr.topRight.y = 15;
    temp->elements[1].mbr.bottomLeft.x = 0;
    temp->elements[1].mbr.bottomLeft.y = 0;
    temp->count++;

    rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[2].mbr.topRight.x = 10;
    temp->elements[2].mbr.topRight.y = 10;
    temp->elements[2].mbr.bottomLeft.x = 0;
    temp->elements[2].mbr.bottomLeft.y = 0;
    temp->count++;

    rtree->root->elements[3].child = (Node*) malloc(sizeof(Node));
    temp->elements[3].mbr.topRight.x = 5;
    temp->elements[3].mbr.topRight.y = 5;
    temp->elements[3].mbr.bottomLeft.x = 0;
    temp->elements[3].mbr.bottomLeft.y = 0;
    temp->count++;
}