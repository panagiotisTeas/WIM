#ifndef WIM_STACK_H
#define WIM_STACK_H

#include "common.h"
#include "ds/dynamic_array.h"

// Stack
typedef struct Stack
{
    DynamicArray    da;
    b8              is_stack_static; // resizable stack
} Stack;

// Stack API

Stack   stackCreate(u64 data_size, u64 capacity, b8 is_stack_static);
void    stackDestroy(Stack* s);

void    stackPush(Stack* s, void* data);
void    stackPop(Stack* s, void* out);
void*   stackPeek(Stack* s);

b8      stackIsEmpty(Stack* s);
u64     stackSize(Stack* s);
void    stackClear(Stack* s);

#endif // WIM_STACK_H