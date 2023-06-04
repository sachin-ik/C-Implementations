//Created by Sachin I K
#include<stdio.h>
#include<stdlib.h>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

Shape s1;
Rectangle r1;
Circle c1;

int main()
{
    Shape_ctor(&s1, 0, 1);
    Shape_moveBy(&s1, 1, -1);
    printf("Shape s1: x=%d, y=%d\n", s1.x, s1.y);

    Rectangle_ctor(&r1, 5, 5, 10, 15);
    Shape_moveBy(&r1.super, 1, -1);
    printf("Rectangle r1: x=%d, y=%d, width=%d, height=%d, area=%d\n", r1.super.x, r1.super.y, r1.width, r1.height, Rectangle_area(&r1));

    // Shape pointer to Rectangle object
    // Here we are using the Shape pointer to access the Rectangle object this is called upcasting or polymorphism
    Shape *sptr = (Shape *)&r1;
    Shape_moveBy(sptr, 1, -1);
    printf("Rectangle r1: x=%d, y=%d, width=%d, height=%d, area=%d\n", r1.super.x, r1.super.y, r1.width, r1.height, Rectangle_area(&r1));
    
    Circle_ctor(&c1, 10, 13, 5);
    // Shape pointer to Circle object
    // Here we are using the same Shape pointer to access the Circle object this is called upcasting or polymorphism
    sptr = (Shape *)&c1;
    Shape_moveBy(sptr, 1, -1);
    printf("Circle c1: x=%d, y=%d, radius=%d, area=%d\n", c1.super.x, c1.super.y, c1.radius, Circle_area(&c1));
    
    
    // Array of Shape pointers
    Shape const *arr[] = {
        (Shape *)&s1,
        (Shape *)&r1,
        (Shape *)&c1,
        (Shape *)0
    };
    
    area_shape(arr);

    return 0;
}
