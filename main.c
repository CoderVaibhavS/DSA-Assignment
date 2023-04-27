#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 4
#define MIN_ENTRIES 2

typedef struct rtree* RTREE;
typedef struct node* NODE;
typedef struct mbr* MBR;

struct rtree {
    NODE root;
    int height;
};

struct node {
    int count;      // no of entries stored
    MBR mbrs[MAX_ENTRIES];      // array of MBRs of the keys of the node
    NODE children[MAX_ENTRIES];     // array of children nodes
};

// Assuming the coordinates to be integers
struct mbr {
    // Min and max coordinates of the rectangle
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};


//creating R Tree function
RTREE createRTree()
{
    
    RTREE r=(RTREE)malloc(sizeof(struct rtree));                     // initialising all parts of the firstnode of the R-Tree to 0
    r->height=0;
    r->root = (NODE)malloc(sizeof(struct node));
    r->root=NULL;
    r->root->count=0;
    // for(int i=0;i<MAX_ENTRIES;i++){
    //     r->root->mbrs[i]->x_max=0;
    //     r->root->mbrs[i]->x_min=0;
    //     r->root->mbrs[i]->y_max=0;
    //     r->root->mbrs[i]->y_min=0;
    // }
    // for(int i=0;i<MAX_ENTRIES;i++){
    //     r->root->children[i]=NULL;
    // }
    return r;
}


//Before creating the search algorithm we will first create the methods required for insertion
//Choosing which Node to insert new elemnt to function as per research paper
int CalculateAreaOfMBR(MBR rec)
{
    int length=abs(rec->x_max-rec->x_min); //this is length of diagonal and not rectangle
    int width=abs(rec->y_max-rec->y_min);  // this is width of diagonal and not rectangle
    int area=(length*width)/2; // thats why there is /2
    return area;
}




MBR chooseSubTree(NODE n)
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
    } else {
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
        
        ChooseLeaf(descendTree(r));
    }
    
 
}
int main() {
    
}