#include "ds/linked_list.h"

#include <memory.h>

// SLL

SLLNode* 
sllNodeCreate(void* data, u64 data_size)
{
    assert(data != NULL);

    SLLNode* node = getMemHook()->malloc_fn(sizeof(SLLNode));

    node->data = getMemHook()->malloc_fn(data_size);
    memcpy(
        node->data,
        data,
        data_size
    );

    node->next = NULL;

    return node;
}

void        
sllNodeDestroy(SLLNode* node)
{
    assert(node != NULL);

    getMemHook()->free_fn(node->data);
    node->data = NULL;
    node->next = NULL;

    getMemHook()->free_fn(node);
}

SLinkedList 
sllCreate(void)
{
    SLinkedList sll = (SLinkedList){
        .head       = NULL,
        .tail       = NULL,
        .node_count = 0
    };

    return sll;
}

void        
sllDelete(SLinkedList* sll)
{
    assert(sll != NULL);

    while (sllDeleteHead(sll) == WIM_TRUE) continue;

    sll->head       = NULL;
    sll->tail       = NULL;
    sll->node_count = 0;
}

void 
sllInsertHead(SLinkedList* sll, void* data, u64 data_size)
{
    assert(sll  != NULL);
    assert(data != NULL);

    SLLNode* node = sllNodeCreate(data, data_size);
    if (sll->node_count == 0)
    {
        sll->head = node;
        sll->tail = node;
    }
    else
    {
        node->next  = sll->head;
        sll->head   = node;
    }

    sll->node_count++;
}

b8        
sllDeleteHead(SLinkedList* sll)
{
    assert(sll != NULL);
    
    if (sll->node_count == 0) return WIM_FALSE;

    SLLNode* new_head = sll->head->next;
    sllNodeDestroy(sll->head);
    sll->head = new_head;
    sll->node_count--;

    if (sll->node_count == 0) sll->tail = NULL;

    return WIM_TRUE;
}

void 
sllInsertTail(SLinkedList* sll, void* data, u64 data_size)
{
    assert(sll  != NULL);
    assert(data != NULL);

    SLLNode* node = sllNodeCreate(data, data_size);
    if (sll->node_count == 0)
    {
        sll->head = node;
        sll->tail = node;
    }
    else
    {
        sll->tail->next = node;
        sll->tail       = node;
    }

    sll->node_count++;
}

b8        
sllDeleteTail(SLinkedList* sll)
{
    assert(sll != NULL);
    
    if (sll->node_count == 0) return WIM_FALSE;
    if (sll->node_count == 1) return sllDeleteHead(sll);

    SLLNode* tmp    = sll->head;
    // SLLNode* prev   = NULL;

    while (tmp->next->next != NULL)
    {
        // prev    = tmp;
        tmp     = tmp->next;
    }

    sllNodeDestroy(tmp->next);
    tmp->next = NULL;
    sll->tail = tmp;
    sll->node_count--;

    return WIM_TRUE;
}

void 
sllInsertAt(SLinkedList* sll, void* data, u64 data_size, u64 index)
{
    assert(sll  != NULL);
    assert(data != NULL);
    
    if (sll->head == NULL || index == 0)    { sllInsertHead(sll, data, data_size); return; }
    if (index >= sll->node_count)           { sllInsertTail(sll, data, data_size); return; }

    SLLNode* tmp = sll->head;
    while (index > 1)
    {
        tmp = tmp->next;
        index--;
    }

    SLLNode* node   = sllNodeCreate(data, data_size);
    node->next      = tmp->next;
    tmp->next       = node;

    sll->node_count++;
}

b8      
sllDeleteAt(SLinkedList* sll, u64 index)
{
    assert(sll != NULL);

    if (sll->node_count == 0)           return WIM_FALSE;
    if (index == 0)                     return sllDeleteHead(sll);
    if (index >= sll->node_count - 1)   return sllDeleteTail(sll);

    SLLNode* tmp    = sll->head;
    SLLNode* prev   = NULL;
    while (index > 0)
    {
        prev    = tmp;
        tmp     = tmp->next;
        index--;
    }

    prev->next = tmp->next;

    sllNodeDestroy(tmp);
    sll->node_count--;

    return WIM_TRUE;
}

u64 
sllGetNodeCount(SLinkedList* sll)
{
    return sll->node_count;
}

// DLL

DLLNode*    
dllNodeCreate(void* data, u64 data_size)
{
    assert(data != NULL);

    DLLNode* node = getMemHook()->malloc_fn(sizeof(DLLNode));

    node->data = getMemHook()->malloc_fn(data_size);
    memcpy(
        node->data,
        data,
        data_size
    );

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void        
dllNodeDestroy(DLLNode* node)
{
    assert(node != NULL);

    getMemHook()->free_fn(node->data);
    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;

    getMemHook()->free_fn(node);
}

DLinkedList 
dllCreate(void)
{
    DLinkedList dll = (DLinkedList){
        .head       = NULL,
        .tail       = NULL,
        .node_count = 0
    };

    return dll;
}

void        
dllDelete(DLinkedList* dll)
{
    assert(dll != NULL);

    while (dllDeleteHead(dll) == WIM_TRUE) continue;

    dll->head       = NULL;
    dll->tail       = NULL;
    dll->node_count = 0;
}

void    
dllInsertHead(DLinkedList* dll, void* data, u64 data_size)
{
    assert(dll  != NULL);
    assert(data != NULL);

    DLLNode* node = dllNodeCreate(data, data_size);
    if (dll->node_count == 0)
    {
        dll->head = node;
        dll->tail = node;
    }
    else
    {
        dll->head->prev = node;
        node->next      = dll->head;
        dll->head       = node;
    }

    dll->node_count++;
}

b8      
dllDeleteHead(DLinkedList* dll)
{
    assert(dll != NULL);
    
    if (dll->node_count == 0) return WIM_FALSE;

    DLLNode* new_head = dll->head->next;
    dllNodeDestroy(dll->head);
    dll->head           = new_head;
    dll->head-> prev    = NULL;
    dll->node_count--;

    if (dll->node_count == 0) dll->tail = NULL;

    return WIM_TRUE;
}

void    
dllInsertTail(DLinkedList* dll, void* data, u64 data_size)
{
    assert(dll  != NULL);
    assert(data != NULL);

    DLLNode* node = dllNodeCreate(data, data_size);
    if (dll->node_count == 0)
    {
        dll->head = node;
        dll->tail = node;
    }
    else
    {
        dll->tail->next = node;
        node->prev      = dll->tail;
        dll->tail       = node;
    }

    dll->node_count++;
}

b8      
dllDeleteTail(DLinkedList* dll)
{
    assert(dll != NULL);
    
    if (dll->node_count == 0) return WIM_FALSE;
    if (dll->node_count == 1) return dllDeleteHead(dll);

    DLLNode* new_tail = dll->tail->prev;
    dllNodeDestroy(dll->tail);
    dll->tail       = new_tail;
    dll->tail->next = NULL;
    dll->node_count--;

    if (dll->node_count == 0) dll->head = NULL;

    return WIM_TRUE;
}

void    
dllInsertAt(DLinkedList* dll, void* data, u64 data_size, u64 index)
{
    assert(dll  != NULL);
    assert(data != NULL);
    
    if (dll->head == NULL || index == 0)    { dllInsertHead(dll, data, data_size); return; }
    if (index >= dll->node_count)           { dllInsertTail(dll, data, data_size); return; }

    DLLNode* tmp = NULL;
    if (index <= dll->node_count / 2)
    {
        tmp = dll->head;
        while (index > 1) { tmp = tmp->next; index--; }
    }
    else
    {
        u64 reverse_index = dll->node_count - index;
        tmp = dll->tail;
        while (reverse_index > 0) { tmp = tmp->prev; reverse_index--; }
    }

    DLLNode* node   = dllNodeCreate(data, data_size);
    node->next      = tmp->next;
    node->prev      = tmp;

    tmp->next->prev = node;
    tmp->next       = node;

    dll->node_count++;
}

b8      
dllDeleteAt(DLinkedList* dll, u64 index)
{
    assert(dll != NULL);

    if (dll->node_count == 0)           return WIM_FALSE;
    if (index == 0)                     return dllDeleteHead(dll);
    if (index >= dll->node_count - 1)   return dllDeleteTail(dll);

    DLLNode* tmp = NULL;
    if (index <= dll->node_count / 2)
    {
        tmp = dll->head;
        while (index > 0) { tmp = tmp->next; index--; }
    }
    else
    {
        u64 reverse_index = (dll->node_count - 1) - index;
        tmp = dll->tail;
        while (reverse_index > 0) { tmp = tmp->prev; reverse_index--; }
    }

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    dllNodeDestroy(tmp);
    dll->node_count--;

    return WIM_TRUE;
}

u64 
dllGetNodeCount(DLinkedList* dll)
{
    return dll->node_count;
}