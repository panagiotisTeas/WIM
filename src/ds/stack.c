#include "ds/stack.h"

#include <memory.h>

// -------------
// --- Stack ---
// -------------

Stack   
stackCreate(u64 data_size, u64 capacity, b8 is_stack_static)
{
    Stack s = (Stack){
        .da                 = daCreate(data_size, capacity),
        .is_stack_static    = is_stack_static
    };

    return s;
}

void    
stackDestroy(Stack* s)
{
    assert(s != NULL);

    daDestroy(&s->da);
}

void    
stackPush(Stack* s, void* data)
{
    assert(s    != NULL);
    assert(data != NULL);

    if (s->is_stack_static == WIM_TRUE && daGetSize(&s->da) == daGetCapacity(&s->da)) return;

    daPushBack(&s->da, data);
}

void 
stackPop(Stack* s, void* out)
{
    assert(s   != NULL);
    assert(out != NULL);
    
    if (stackIsEmpty(s)) return;
    
    void* data = daGet(&s->da, daGetSize(&s->da) - 1);
    memcpy(
        out, 
        data, 
        s->da.data_size
    );
    
    daPopBack(&s->da);
}

void*   
stackPeek(Stack* s)
{
    assert(s != NULL);
    assert(!stackIsEmpty(s));

    return daGet(&s->da, daGetSize(&s->da) - 1);
}

b8  
stackIsEmpty(Stack* s)
{
    assert(s != NULL);

    return daIsEmpty(&s->da);
}

u64 
stackSize(Stack* s)
{
    assert(s != NULL);

    return daGetSize(&s->da);
}

void 
stackClear(Stack* s)
{
    assert(s != NULL);

    void* tmp = getMemHook()->malloc_fn(s->da.data_size);
    while (stackIsEmpty(s) == WIM_FALSE) stackPop(s, tmp);
    getMemHook()->free_fn(tmp);
}
