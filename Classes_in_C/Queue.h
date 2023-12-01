#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue; 

//create a queue structure
struct Queue
{
    int front, rear, size;
    unsigned int capacity;
    void** array; //array of void pointers
};

//Queue functions
Queue* Queue_create(unsigned int capacity);
int Queue_isFull(Queue* queue);
int Queue_isEmpty(Queue* queue);
void Queue_enqueue(Queue* queue, void* item);
void* Queue_dequeue(Queue* queue);
void* Queue_front(Queue* queue);
void* Queue_rear(Queue* queue);
void Queue_destroy(Queue* queue);

#endif