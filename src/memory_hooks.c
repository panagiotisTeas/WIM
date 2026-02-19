#include "memory_hooks.h"

#include <stdlib.h>
#include <assert.h>

static MemoryHook g_mem_hooks = {
    .malloc_fn  = malloc,
    .calloc_fn  = calloc,
    .realloc_fn = realloc,
    .free_fn    = free,
};

void 
setMallocFn(void* (*malloc_fn)(size_t __size))
{
    assert(malloc_fn != NULL);

    g_mem_hooks.malloc_fn = malloc_fn;
}

void 
setCallocFn(void* (*calloc_fn)(size_t __nmemb, size_t __size))
{
    assert(calloc_fn != NULL);

    g_mem_hooks.calloc_fn = calloc_fn;
}

void 
setReallocFn(void* (*realloc_fn)(void* __ptr, size_t __size))
{
    assert(realloc_fn != NULL);

    g_mem_hooks.realloc_fn = realloc_fn;
}

void 
setFreeFn(void (*free_fn)(void* __ptr))
{
    assert(free_fn != NULL);

    g_mem_hooks.free_fn = free_fn;
}

MemoryHook* 
getMemHook(void)
{
    return &g_mem_hooks;
}