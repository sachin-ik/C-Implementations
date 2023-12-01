//create a active object class and it functions
#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include "Queue.h"

//Active Object contains a thread and a queue
typedef struct ActiveObject ActiveObject;

typedef void (*ThreadFunction)(ActiveObject * const me);

struct ActiveObject
{
    //Here thread should be a function pointer
    ThreadFunction aoThread;    //thread function
    Queue *aoQueue; //queue of requests
};

//Active Object functions
ActiveObject* ActiveObject_constructor(ThreadFunction thread, unsigned int queueSize);
void ActiveObject_start(ActiveObject * const me);
void ActiveObject_enqueue(ActiveObject * const me, void *request);
void ActiveObject_destructor(ActiveObject * const me);

#endif