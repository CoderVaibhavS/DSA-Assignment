#include <stdlib.h>
#include "rtree.h"

int main() {

    RTREE rtree = (RTREE) malloc(sizeof(struct rtree));
    rtree->height = 0;

    rtree->root = (NODE) malloc(sizeof(struct node));
    rtree->height++;
    rtree->root->count = 0;


    rtree->root->mbrs[0].topRight.x = 100;
    rtree->root->mbrs[0].topRight.y = 100;
    rtree->root->mbrs[0].bottomLeft.x = 75;
    rtree->root->mbrs[0].bottomLeft.y = 75;
    rtree->root->count++;


    rtree->root->mbrs[1].topRight.x = 75;
    rtree->root->mbrs[1].topRight.y = 75;
    rtree->root->mbrs[1].bottomLeft.x = 50;
    rtree->root->mbrs[1].bottomLeft.y = 50;
    rtree->root->count++;

    rtree->root->mbrs[2].topRight.x = 50;
    rtree->root->mbrs[2].topRight.y = 50;
    rtree->root->mbrs[2].bottomLeft.x = 25;
    rtree->root->mbrs[2].bottomLeft.y = 25;
    rtree->root->count++;
    
    rtree->root->mbrs[3].topRight.x = 25;
    rtree->root->mbrs[3].topRight.y = 25;
    rtree->root->mbrs[3].bottomLeft.x = 0;
    rtree->root->mbrs[3].bottomLeft.y = 0;
    rtree->root->count++;

    NODE temp;

    /* -----------------------------------------CHILD 1---------------------------------------- */

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp = rtree->root->children[0];
    temp->count = 0;
    temp->mbrs[0].topRight.x = 95;
    temp->mbrs[0].topRight.y = 95;
    temp->mbrs[0].bottomLeft.x = 75;
    temp->mbrs[0].bottomLeft.y = 75;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[1].topRight.x = 90;
    temp->mbrs[1].topRight.y = 90;
    temp->mbrs[1].bottomLeft.x = 75;
    temp->mbrs[1].bottomLeft.y = 75;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[2].topRight.x = 85;
    temp->mbrs[2].topRight.y = 85;
    temp->mbrs[2].bottomLeft.x = 75;
    temp->mbrs[2].bottomLeft.y = 75;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[3].topRight.x = 80;
    temp->mbrs[3].topRight.y = 80;
    temp->mbrs[3].bottomLeft.x = 75;
    temp->mbrs[3].bottomLeft.y = 75;
    temp->count++;

    /* -----------------------------------------CHILD 2---------------------------------------- */

    rtree->root->children[1] = (NODE) malloc(sizeof(struct node));
    temp = rtree->root->children[0];
    temp->count = 0;
    temp->mbrs[0].topRight.x = 70;
    temp->mbrs[0].topRight.y = 70;
    temp->mbrs[0].bottomLeft.x = 50;
    temp->mbrs[0].bottomLeft.y = 50;
    temp->count++;

    rtree->root->children[1] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[1].topRight.x = 65;
    temp->mbrs[1].topRight.y = 65;
    temp->mbrs[1].bottomLeft.x = 50;
    temp->mbrs[1].bottomLeft.y = 50;
    temp->count++;

    rtree->root->children[1] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[2].topRight.x = 60;
    temp->mbrs[2].topRight.y = 60;
    temp->mbrs[2].bottomLeft.x = 50;
    temp->mbrs[2].bottomLeft.y = 50;
    temp->count++;

    rtree->root->children[1] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[3].topRight.x = 55;
    temp->mbrs[3].topRight.y = 55;
    temp->mbrs[3].bottomLeft.x = 50;
    temp->mbrs[3].bottomLeft.y = 50;
    temp->count++;

    /* -----------------------------------------CHILD 3---------------------------------------- */

    rtree->root->children[2] = (NODE) malloc(sizeof(struct node));
    temp = rtree->root->children[2];
    temp->count = 0;
    temp->mbrs[0].topRight.x = 45;
    temp->mbrs[0].topRight.y = 45;
    temp->mbrs[0].bottomLeft.x = 25;
    temp->mbrs[0].bottomLeft.y = 25;
    temp->count++;

    rtree->root->children[2] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[1].topRight.x = 40;
    temp->mbrs[1].topRight.y = 40;
    temp->mbrs[1].bottomLeft.x = 25;
    temp->mbrs[1].bottomLeft.y = 25;
    temp->count++;

    rtree->root->children[2] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[2].topRight.x = 35;
    temp->mbrs[2].topRight.y = 35;
    temp->mbrs[2].bottomLeft.x = 25;
    temp->mbrs[2].bottomLeft.y = 25;
    temp->count++;

    rtree->root->children[2] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[3].topRight.x = 30;
    temp->mbrs[3].topRight.y = 30;
    temp->mbrs[3].bottomLeft.x = 25;
    temp->mbrs[3].bottomLeft.y = 25;
    temp->count++;

    /* -----------------------------------------CHILD 4---------------------------------------- */

    rtree->root->children[3] = (NODE) malloc(sizeof(struct node));
    temp = rtree->root->children[3];
    temp->count = 0;
    temp->mbrs[0].topRight.x = 20;
    temp->mbrs[0].topRight.y = 20;
    temp->mbrs[0].bottomLeft.x = 0;
    temp->mbrs[0].bottomLeft.y = 0;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[1].topRight.x = 15;
    temp->mbrs[1].topRight.y = 15;
    temp->mbrs[1].bottomLeft.x = 0;
    temp->mbrs[1].bottomLeft.y = 0;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[2].topRight.x = 10;
    temp->mbrs[2].topRight.y = 10;
    temp->mbrs[2].bottomLeft.x = 0;
    temp->mbrs[2].bottomLeft.y = 0;
    temp->count++;

    rtree->root->children[0] = (NODE) malloc(sizeof(struct node));
    temp->mbrs[3].topRight.x = 5;
    temp->mbrs[3].topRight.y = 5;
    temp->mbrs[3].bottomLeft.x = 0;
    temp->mbrs[3].bottomLeft.y = 0;
    temp->count++;
}