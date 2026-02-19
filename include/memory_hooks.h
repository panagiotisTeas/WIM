#ifndef WIM_MEMORY_HOOKS_H
#define WIM_MEMORY_HOOKS_H

#include <stddef.h>

typedef struct MemoryHook
{
    void*   (*malloc_fn)(size_t __size);
    void*   (*calloc_fn)(size_t __nmemb, size_t __size);
    void*   (*realloc_fn)(void* __ptr, size_t __size);
    void    (*free_fn)(void* __ptr);
} MemoryHook;

void setMallocFn(void* (*malloc_fn)(size_t __size));
void setCallocFn(void* (*calloc_fn)(size_t __nmemb, size_t __size));
void setReallocFn(void* (*realloc_fn)(void* __ptr, size_t __size));
void setFreeFn(void (*free_fn)(void* __ptr));

MemoryHook* getMemHook(void);

#endif // WIM_MEMORY_HOOKS_H