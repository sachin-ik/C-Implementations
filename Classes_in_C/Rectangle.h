#ifndef RECTANGLE_H
#define RECTANGLE_H

//STEP2:
/*
Create a Rectangle class which is derived from Shape class.
Rectangle class provides width and height of the rectangle and provides constructor function and 
area function to calculate the area of the rectangle.
*/

#include "Shape.h"

typedef struct Rectangle Rectangle;

struct Rectangle{
    Shape super;
    int width;
    int height;
};

void Rectangle_ctor(Rectangle * const me, int x, int y, int width, int height);
int Rectangle_area(Rectangle const * const me);

#endif