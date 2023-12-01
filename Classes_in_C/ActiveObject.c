#include "ActiveObject.h"
#include <stdlib.h>

ActiveObject* ActiveObject_constructor(ThreadFunction thread, unsigned int queueSize)
{
    ActiveObject* ao = (ActiveObject*)malloc(sizeof(ActiveObject));
    ao->aoThread = thread;
    ao->aoQueue = Queue_create(queueSize);
    return ao;
}

void ActiveObject_start(ActiveObject * const me)
{
    me->aoThread(me);
}

void ActiveObject_enqueue(ActiveObject * const me, void *request)
{
    Queue_enqueue(me->aoQueue, request);
}

void ActiveObject_destructor(ActiveObject * const me)
{
    Queue_destroy(me->aoQueue);
    free(me);
}