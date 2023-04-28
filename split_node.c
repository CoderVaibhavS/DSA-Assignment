#include <math.h>
#include <stdlib.h>

#include "rtree.h"

void pickSeeds(Node* node, Rect* r1, Rect* r2)
{
    int max_area = 0, area, area1, area2;  // distance b/w points
    Rect rect, rect1, rect2;

    for (int i = 0; i < node->count; i++)
    {
        for (int j = i + 1; j < node->count; j++)
        {
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

            area = CalculateAreaOfrectangle(rect);
            area1 = CalculateAreaOfrectangle(rect1);
            area2 = CalculateAreaOfrectangle(rect2);

            if (max_area < area - area1 - area2)
            {  // we are selecting the 2 rectangles which have the maximum aread
               // inbetween them when we bound those two rectangles with a
               // bigger rectangle
                max_area = area - area1 - area2;
                *r1 = rect1;
                *r2 = rect2;
            }
        }
    }
}

void pickNext() {}
