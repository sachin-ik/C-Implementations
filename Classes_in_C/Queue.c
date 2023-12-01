// Implement queue functions

#include <stdlib.h>
#include "Queue.h"

Queue* Queue_create(unsigned int capacity)
{
    //queue should store void pointers so that it can store any type of data
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    //array of void pointers to store any type of data in the queue
    queue->array = (void**)malloc(queue->capacity * sizeof(void*));
}

void Queue_enqueue(Queue *queue, void *item)
{
    if (Queue_isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

void* Queue_dequeue(Queue *queue)
{
    if (Queue_isEmpty(queue))
        return (void*)0;
    void * item =  queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}


void Queue_destroy(Queue* queue)
{
    free(queue->array);
    free(queue);
}



int Queue_isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}

int Queue_isEmpty(Queue* queue)
{
    return (queue->size == 0);
}

