//Created by Sachin I K
#include<stdio.h>
#include<stdlib.h>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Queue.h"
#include "ActiveObject.h"

Shape s1;
Rectangle r1;
Circle c1;


void aoThreadFunction(ActiveObject * const me)
{
    //Active object thread should be of infinite loop
    //so that it can process the requests continuously

    //But in this example we are not using infinite loop to avoid blocking the main thread
    //while(1)
    {
        while(!Queue_isEmpty(me->aoQueue))
        {
            void *request = Queue_dequeue(me->aoQueue);
            printf("Request: %d\n", *(int *)request);
            free(request);
        }
    }
}

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

    /*Testing queues*/
    Queue* queue = Queue_create(10);
    int i;
    for(i=0;i<10;i++)
    {
        Queue_enqueue(queue, &i);
    }

    for(i=0;i<10;i++)
    {
        printf("Dequeued: %d\n", *(unsigned int*)Queue_dequeue(queue));
    }

    Queue_destroy(queue);
    //***********************//

    /*Test active objects*/
    //create a active object
    ActiveObject* ao = ActiveObject_constructor(&aoThreadFunction, 10);
    
    for(i=0;i<10;i++)
    {
        int *request = (int *)malloc(sizeof(int));
        *request = i;
        ActiveObject_enqueue(ao, request);
    }
    ActiveObject_start(ao);
    ActiveObject_destructor(ao);
    return 0;
}
