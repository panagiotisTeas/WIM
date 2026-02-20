#ifndef WIM_DYNAMIC_ARRAY_H
#define WIM_DYNAMIC_ARRAY_H

#include "common.h"

// Dynamic Array
typedef struct DynamicArray
{
    void*   data_buffer;
    u64     data_size;
    u64     buffer_size;
    u64     buffer_capacity;
} DynamicArray;

// Dynamic Array API

DynamicArray    daCreate(u64 data_size, u64 buffer_init_capacity);
void            daDestroy(DynamicArray* da);

u64 daGetSize(DynamicArray* da);
u64 daGetCapacity(DynamicArray* da);

void daPushBack(DynamicArray* da, void* data);
void daPopBack(DynamicArray* da);
void daInsertAt(DynamicArray* da, void* data, u64 index);
void daDeleteAt(DynamicArray* da, u64 index);

void*   daGet(DynamicArray* da, u64 index);
void    daSet(DynamicArray* da, u64 index, void* data);

// capacity -> 2 * capacity
void daGrowArray(DynamicArray* da);
// capacity -> capacity / 2
void daShrinkArray(DynamicArray* da);

b8 daIsEmpty(DynamicArray* da);

#endif // WIM_DYNAMIC_ARRAY_H