#ifndef WIM_HEAP_H
#define WIM_HEAP_H

#include "common.h"
#include "ds/dynamic_array.h"

// Heap
typedef struct Heap
{
    DynamicArray    da;
    b8              (*comparator)(void* a, void* b);
} Heap;

// Heap API

Heap heapCreate(u64 data_size, u64 buffer_init_capacity, b8 (*comparator)(void* a, void* b));
void heapDestroy(Heap* heap);

void    heapInsert(Heap* heap, void* data);
void    heapExtract(Heap* heap, void* out);

b8      heapIsEmpty(Heap* heap);
u64     heapSize(Heap* heap);
void    heapSwim(Heap* heap, u64 index);
void    heapSink(Heap* heap, u64 index);
void    heapSwap(Heap* heap, u64 a, u64 b);

#endif // WIM_HEAP_H