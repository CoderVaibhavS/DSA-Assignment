#include "rtree.h"
#include <stdio.h>
#include <stdlib.h>
//Before creating the search algorithm we will first create the methods required for insertion
//Choosing which Node to insert new elemnt to function as per research paper
int CalculateAreaOfMBR(MBR rec)
{
    int length=abs(rec.topRight.x -rec.bottomLeft.x); //this is length of rectangle
    int width=abs(rec.topRight.y-rec.bottomLeft.y);  // this is width of rectangle
    int area=(length*width); 
    return area;
}




MBR chooseSubTree(NODE n) //read
{
    
        int area1=CalculateAreaOfMBR(n->mbrs[0]);
        int area2=CalculateAreaOfMBR(n->mbrs[1]);
        int area3=CalculateAreaOfMBR(n->mbrs[2]);
        int area4=CalculateAreaOfMBR(n->mbrs[3]);

        //finding the rectangle with the minimum area
        int min_area = CalculateAreaOfMBR(n->mbrs[0]);  // Assume the first area is the minimum
        int area;

        area = CalculateAreaOfMBR(n->mbrs[1]);
        if (area < min_area) {
        min_area = area;
        }

        area = CalculateAreaOfMBR(n->mbrs[2]);
        if (area < min_area) {
        min_area = area;
        }

        area = CalculateAreaOfMBR(n->mbrs[3]);
        if (area < min_area) {
        min_area = area;
        }

        for(int i=0;i<MAX_ENTRIES && CalculateAreaOfMBR(n->mbrs[i])==area;i++)
        {

                return n->mbrs[i];        
        }
     //this else part is not handled properly
}



int LeafCheck(NODE n)
{
    if(n->children[0]==NULL && n->children[1]==NULL && n->children[2]==NULL && n->children[3]==NULL)
    {
        return 1;
    }
    else return 0;
}

NODE descendTree(NODE n)
{     
    int status1 = LeafCheck(n->children[0]);
    int status2 = LeafCheck(n->children[1]);
    int status3 = LeafCheck(n->children[2]);
    int status4 = LeafCheck(n->children[3]);

    if (status1 == 1) {
        return n->children[0];
    } else if (status2 == 1) {
        return n->children[1];
    } else if (status3 == 1) {
        return n->children[2];
    } else if (status4 == 1) {
        return n->children[3];
    } else { //else to recrusively check if its leaf node and if its not descend down the tree
        NODE result = NULL;
        result = descendTree(n->children[0]);
        if (result != NULL) {
            return result;
        }

        result = descendTree(n->children[1]);
        if (result != NULL) {
            return result;
        }

        result = descendTree(n->children[2]);
        if (result != NULL) {
            return result;
        }

        result = descendTree(n->children[3]);
        return result;
    }
}

//NOTE while implementing ChooseLeaf in the main function we will feed it the root node of the tree
MBR ChooseLeaf(NODE r) //this method is still incomplete, I am yet to finish this
{
    //Start at root node
    int status=LeafCheck(r);
    if(status==1)
    {
        return r->mbrs[0];
    }
    else
    {
        
        chooseSubTree(ChooseLeaf(descendTree(r))); //recursively calling ChooseLeaf to call CL2,CL3 and CL4
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------