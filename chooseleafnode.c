#include <math.h>
#include <stdio.h>

#include "rtree.h"

Node_ele* chooseSubTree(Node* node, Rect rectAdd) //rectAdd is the new MBR to be added and the various nodeele are contained in the node and we must select one of the node_ele to descend down from or in other words choose the appropriate subtree
{//this is the chooseSubTree algorithm which is a sub-algorithm in chooseLeaf                                                 
    int ele = 0; //we are using ele as an index which will be of significance importance as you read the code further

    int areaMin = calculateAreaOfRectangle(node->elements[0]->mbr); //intialising areaMin to first nodeele
    int areaEnlarge = calcAreaEnlargement(node->elements[0]->mbr, rectAdd); //initialising areaEnlarge to the rectangle of minimum area bounding first node_ele mbr and the rectAdd being added

    for (int i = 1; i < node->count; i++) //iterating through all the other node_ele other than the first one because we already went through it in the previous step
    {
        if (node->elements[i] != NULL)//if statement designed this way because if the node->element[i] was null the functions used under it would give bad and incorrect results
        {
            int area = calculateAreaOfRectangle(node->elements[i]->mbr); //doing the similar thing we did for the lines where we initialised areaMin and areaEnlarge
            int areaE = calcAreaEnlargement(node->elements[i]->mbr, rectAdd);
            
            if (areaE < areaEnlarge) //we are finding that rectangle among many rectangles that require the minimum area to enlarge to accomodate the new added rectangle
            {
                areaMin = area; //alloting the areas to their respective variables as per the logic mentioned above
                areaEnlarge = areaE;
                ele = i;
            }
            else if (areaE == areaEnlarge)//handling the case incase the areas of enlargment being compared for various rectangles comes out to be equal
            {
                if (area < areaMin)//as per the researcg paper we handle this case by simply alloting the rectangle which has the smaller area and the enlarged rectangle which encloses this and the new added rectangle to its appropriate variables 
                {
                    areaMin = area;//alloting the areas to their respective variables as per the logic mentioned above
                    areaEnlarge = areaE;
                    ele = i;
                }
            }
        }
        else//there is no other case possible hence simply breaking out of the loop
        {
            break;
        }
    }

    return node->elements[ele]; //finally returning the appropriate subtree chosen after implementing the "area logics" given according to the research paper
}

Node* ChooseLeaf(Rtree* tree, Rect rectAdd) //chooseleaf function which contains the various sub-algorithms too
{
    Node* node = tree->root;//creating a variable root which simply points to the tree's root
    while (!node->is_leaf)//running loop until we reach a leaf
    {
        node = chooseSubTree(node, rectAdd)->child;//this is to choose the appropriate sub-tree to descend down to as we iterate through the loop
    }
    Rect mbr = node->parent->mbr;//handling the other attributes present in struct node appropriately to avoid having those attributes point to random values
    // printf("(%d, %d) -> (%d, %d)", mbr.bottomLeft.x, mbr.bottomLeft.y, mbr.topRight.x, mbr.topRight.y);
    return node; //finally we return the correct lead node
}
