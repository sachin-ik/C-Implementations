#ifndef SHAPE_H
#define SHAPE_H

//STEP1:
/* Shape is a base class which provides location of the shape in a 2D plane and provides 
   constructor function and moveBy function to move the shape by a given amount in x and y direction.
*/

typedef struct Shape Shape;

struct Shape {
    //virtual function table should be the first data member of the class(In C++ it is done automatically)
    struct ShapeVtbl const *vptr; //pointer to constant ShapeVtbl object
    /*data members*/
    int x;
    int y;
};

//To implement virtual functions in C, we use function pointers
struct ShapeVtbl {
    int (*area)(Shape const * const me); //area is a function pointer
};

//virtual call (late binding/runtime binding/dynamic binding)
static inline int Shape_area_vcall(Shape const * const me) {
    //Here the objects points to corresponding area function of the derived class
    //Ex: When &R1 is passed to Shape_area_vcall, it points to Rectangle_area function
    //    When &C1 is passed to Shape_area_vcall, it points to Circle_area function
    //    When &S1 is passed to Shape_area_vcall, it points to Shape_area function
    return (*me->vptr->area)(me); //(*me->vptr->area) is a function pointer
}

//function to draw a shape from array of pointers to different Shape objects
void area_shape(Shape const *arr[]);

//me is a pointer to the object being created
//me is a constant pointer to a Shape object
//me is used to access the data members of a particular object
void Shape_ctor(Shape * const me, int x, int y);
void Shape_moveBy(Shape * const me, int dx, int dy);

#endif