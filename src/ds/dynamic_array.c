#include "ds/dynamic_array.h"

#include <memory.h>

DynamicArray    
daCreate(u64 data_size, u64 buffer_init_capacity)
{
    assert(buffer_init_capacity != 0);

    DynamicArray da = (DynamicArray){
        .data_buffer        = getMemHook()->malloc_fn(data_size * buffer_init_capacity),
        .data_size          = data_size,
        .buffer_size        = 0,
        .buffer_capacity    = buffer_init_capacity,
    };

    return da;
}

void            
daDestroy(DynamicArray* da)
{
    assert(da != NULL);

    getMemHook()->free_fn(da->data_buffer);
}

u64 
daGetSize(DynamicArray* da)
{
    assert(da != NULL);

    return da->buffer_size;
}

u64 
daGetCapacity(DynamicArray* da)
{
    assert(da != NULL);

    return da->buffer_capacity;
}

void 
daPushBack(DynamicArray* da, void* data)
{
    assert(da   != NULL);
    assert(data != NULL);

    if (da->buffer_size >= da->buffer_capacity) daGrowArray(da);

    memcpy(
        (void*)((u8*)da->data_buffer + da->buffer_size * da->data_size),
        data,
        da->data_size
    );

    da->buffer_size++;
}

void 
daPopBack(DynamicArray* da)
{
    assert(da               != NULL);
    assert(daIsEmpty(da)    == WIM_FALSE);

    da->buffer_size--;

    // if (da->buffer_size == (da->buffer_capacity / 2)) daShrinkArray(da);
}

void 
daInsertAt(DynamicArray* da, void* data, u64 index)
{
    assert(da   != NULL);
    assert(data != NULL);
    assert(index <= da->buffer_size);

    if (da->buffer_size >= da->buffer_capacity) daGrowArray(da);

    memmove(
        (void*)((u8*)da->data_buffer + (index + 1) * da->data_size),
        (void*)((u8*)da->data_buffer + (index + 0) * da->data_size),
        da->data_size * (da->buffer_size - index)
    );

    memcpy(
        (void*)((u8*)da->data_buffer + index * da->data_size),
        data,
        da->data_size
    );

    da->buffer_size++;
}

void 
daDeleteAt(DynamicArray* da, u64 index)
{
    assert(da   != NULL);
    assert(index < da->buffer_size); 

    memmove(
        (void*)((u8*)da->data_buffer + (index + 0) * da->data_size),
        (void*)((u8*)da->data_buffer + (index + 1) * da->data_size),
        da->data_size * (da->buffer_size - index - 1)
    );

    da->buffer_size--;

    // if (da->buffer_size == (da->buffer_capacity / 2)) daShrinkArray(da);
}

void* daGet(DynamicArray* da, u64 index)
{
    assert(da   != NULL);
    assert(index < da->buffer_size);

    return (void*)((u8*)da->data_buffer + index * da->data_size);
}

void    
daSet(DynamicArray* da, u64 index, void* data)
{
    assert(da   != NULL);
    assert(data != NULL);
    assert(index < da->buffer_size);

    memcpy(
        (void*)((u8*)da->data_buffer + index * da->data_size),
        data,
        da->data_size
    );
}

void 
daGrowArray(DynamicArray* da)
{
    assert(da != NULL);

    da->buffer_capacity    *= 2;
    da->data_buffer         = getMemHook()->realloc_fn(da->data_buffer, da->data_size * da->buffer_capacity);
}

void 
daShrinkArray(DynamicArray* da)
{
    assert(da != NULL);

    da->buffer_capacity    /= 2;
    da->data_buffer         = getMemHook()->realloc_fn(da->data_buffer, da->data_size * da->buffer_capacity);
}

b8 
daIsEmpty(DynamicArray* da)
{
    assert(da != NULL);

    return (da->buffer_size == 0);
}