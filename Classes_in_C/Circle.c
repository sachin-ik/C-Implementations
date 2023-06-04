#include "Circle.h"

void Circle_ctor(Circle * const me, int x, int y, int radius) {
    static const struct ShapeVtbl vtbl = {
        &Circle_area
    };

    Shape_ctor(&me->super, x, y); // call super constructor so that x and y are initialized
    me->super.vptr = &vtbl; //adjust the vptr
    me->radius = radius;
}

int Circle_area(Circle const * const me) {
    return (3 * me->radius * me->radius);
}