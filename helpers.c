#include <stdio.h>

#include "rtree.h"

int calculateAreaOfRectangle(Rect rect)
{
    int height = abs(rect.topRight.x - rect.bottomLeft.x);
    int width = abs(rect.topRight.y - rect.bottomLeft.y);
}
