#include "ds/heap.h"

#include <memory.h>

// ------------
// --- Heap ---
// ------------

Heap 
heapCreate(u64 data_size, u64 buffer_init_capacity, b8 (*comparator)(void* a, void* b))
{
    assert(comparator != NULL);

    Heap h = (Heap){
        .da         = daCreate(data_size, buffer_init_capacity),
        .comparator = comparator
    };

    return h;
}

void 
heapDestroy(Heap* heap)
{
    assert(heap != NULL);

    daDestroy(&heap->da);
    heap->comparator = NULL;
}

void    
heapInsert(Heap* heap, void* data)
{
    assert(heap != NULL);
    assert(data != NULL);

    daPushBack(&heap->da, data);
    heapSwim(heap, daGetSize(&heap->da) - 1);
}

void 
heapExtract(Heap* heap, void* out)
{
    assert(heap != NULL);
    assert(out  != NULL);

    if (heapIsEmpty(heap) == WIM_TRUE) return;

    heapSwap(heap, 0, daGetSize(&heap->da) - 1);
    memcpy(out, daGet(&heap->da, daGetSize(&heap->da) - 1), heap->da.data_size);
    daPopBack(&heap->da);
    if (daGetSize(&heap->da) > 0) heapSink(heap, 0);
}

b8      
heapIsEmpty(Heap* heap)
{
    assert(heap != NULL);

    return (daGetSize(&heap->da) == 0);
}

u64     
heapSize(Heap* heap)
{
    assert(heap != NULL);

    return daGetSize(&heap->da);
}

void    
heapSink(Heap* heap, u64 index)
{
    assert(heap     != NULL);
    assert(index     < daGetSize(&heap->da));

    while (2 * index + 1 < daGetSize(&heap->da))
    {
        u64 j = 2 * index + 1;
        
        if (j + 1 < daGetSize(&heap->da) && 
            heap->comparator(
                daGet(&heap->da, j),
                daGet(&heap->da, j + 1)
            )) j++;

        if (!heap->comparator(
            daGet(&heap->da, index),
            daGet(&heap->da, j)
        )) break;

        heapSwap(heap, index, j);
        index = j;
    } 
}

void    
heapSwim(Heap* heap, u64 index)
{
    assert(heap     != NULL);
    assert(index     < daGetSize(&heap->da));

    while (index > 0 &&
        heap->comparator(
            daGet(&heap->da, (index - 1) / 2), 
            daGet(&heap->da, index)
        ))
    {
        heapSwap(heap, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
    
}

void    
heapSwap(Heap* heap, u64 a, u64 b)
{
    assert(heap != NULL);
    assert(a    < daGetSize(&heap->da));
    assert(b    < daGetSize(&heap->da));

    u8* ptr_a = (uint8_t*)daGet(&heap->da, a);
    u8* ptr_b = (uint8_t*)daGet(&heap->da, b);
    u8  temp[heap->da.data_size];

    memcpy(temp,  ptr_a, heap->da.data_size);
    memcpy(ptr_a, ptr_b, heap->da.data_size);
    memcpy(ptr_b, temp,  heap->da.data_size);
}
