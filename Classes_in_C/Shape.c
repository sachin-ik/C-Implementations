#include "Shape.h"
#include <stdio.h>

static int Shape_area(Shape const * const me);

static const struct ShapeVtbl vtable = {
        &Shape_area
};

void Shape_ctor(Shape * const me, int x, int y) {
    me->vptr = &vtable;
    me->x = x;
    me->y = y;
}

void Shape_moveBy(Shape * const me, int dx, int dy) {
    me->x += dx;
    me->y += dy;
}

// print area of all shapes in the array
//based on ptr type it will call the respective area function
void area_shape(const Shape *arr[])
{
    int i=0;
    for(i=0; arr[i] != (Shape*)0; i++)
    {
        printf("Area of Shape: %d\n",Shape_area_vcall(arr[i]));
    }
}

// call the area function of the object
int Shape_area(Shape const * const me)
{
    (void)me;
    return 0;
}

