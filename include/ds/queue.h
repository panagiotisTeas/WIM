#ifndef WIM_QUEUE_H
#define WIM_QUEUE_H

#include "common.h"
#include "ds/dynamic_array.h"
#include "ds/linked_list.h"

// Queue
typedef struct Queue
{
    SLinkedList     sll;
    u64             capacity;
} Queue;

// Circular Queue
//TODO

// Queue API

Queue   qCreate(u64 capacity);
void    qDestroy(Queue* q);

void    qEnqueue(Queue* q, void* data, u64 data_size);
void    qDequeue(Queue* q, void* out, u64 data_size);
void*   qPeek(Queue* q);

b8      qIsEmpty(Queue* q);
u64     qSize(Queue* q);
void    qClear(Queue* q);

// Circular Queue API
//TODO

#endif // WIM_QUEUE_H