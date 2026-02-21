#include "ds/queue.h"

#include <memory.h>

// -------------
// --- Queue ---
// -------------

Queue   
qCreate(u64 capacity)
{
    assert(capacity != 0);
    
    Queue q = (Queue){
        .sll        = sllCreate(),
        .capacity   = capacity
    };

    return q;
}

void    
qDestroy(Queue* q)
{
    assert(q != NULL);

    sllDelete(&q->sll);
}

void    
qEnqueue(Queue* q, void* data, u64 data_size)
{
    assert(q    != NULL);
    assert(data != NULL);

    if (sllGetNodeCount(&q->sll) == q->capacity) return;

    sllInsertTail(&q->sll, data, data_size);
}

void    
qDequeue(Queue* q, void* out, u64 data_size)
{
    assert(q    != NULL);
    assert(out  != NULL);

    if (qIsEmpty(q) == WIM_TRUE) return;

    void* data = q->sll.head->data;
    memcpy(
        out,
        data,
        data_size
    );

    sllDeleteHead(&q->sll);
}

void*   
qPeek(Queue* q)
{
    assert(q != NULL);
    if (qIsEmpty(q) == WIM_TRUE) return NULL;
    
    return q->sll.head->data;
}

b8     
qIsEmpty(Queue* q)
{
    assert(q != NULL);

    return (sllGetNodeCount(&q->sll) == 0);
}

u64     
qSize(Queue* q)
{
    assert(q != NULL);

    return sllGetNodeCount(&q->sll);
}

void    
qClear(Queue* q)
{
    while(q->sll.head != NULL) sllDeleteHead(&q->sll);
}