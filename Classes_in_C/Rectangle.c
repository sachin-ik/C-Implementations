#include "Rectangle.h"

void Rectangle_ctor(Rectangle * const me, int x, int y, int width, int height) {
    static const struct ShapeVtbl  vtbl = {
        &Rectangle_area
    };
    Shape_ctor(&me->super, x, y); // call super constructor so that x and y are initialized
    me->super.vptr = &vtbl; //adjust the vptr
    me->width = width;
    me->height = height;
}

int Rectangle_area(Rectangle const * const me) {
    return (me->width * me->height);
}