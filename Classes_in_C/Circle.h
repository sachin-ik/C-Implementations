#ifndef CIRCLE_H
#define CIRCLE_H

//STEP2:
/*
Create a Circle class which is derived from Shape class.
Circle class provides radius of the Circle and provides constructor function and 
area function to calculate the area of the Circle.
*/

#include "Shape.h"

typedef struct Circle Circle;

struct Circle{
    Shape super;
    int radius;
};

void Circle_ctor(Circle * const me, int x, int y, int radius);
int Circle_area(Circle const * const me);

#endif