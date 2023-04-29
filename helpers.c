#include <stdio.h>
#include <math.h>
#include "rtree.h"

Rect createMBR(Rect rect1, Rect rect2)
{
    Rect rect;
    rect.topRight.x = fmax(rect1.topRight.x, rect2.topRight.x);  // we are doing this to find the rectangle of
                                                                 // smallest area that encloses rect1 and rect2
    rect.topRight.y = fmax(rect1.topRight.y, rect2.topRight.y);
    rect.bottomLeft.x = fmin(rect1.bottomLeft.x, rect2.bottomLeft.x);
    rect.bottomLeft.y = fmin(rect1.bottomLeft.y, rect2.bottomLeft.y);
    
    return rect;
}

int calculateAreaOfRectangle(Rect rect)  // Returns the area of the rectangle
{
    int length = abs(rect.topRight.x -
                     rect.bottomLeft.x);  // this is length of rectangle
    int width =
        abs(rect.topRight.y - rect.bottomLeft.y);  // this is width of rectangle
    int area = (length * width);  // area of rectangle= length *breadth
    return area;                  // returns area of the rectangle
}
