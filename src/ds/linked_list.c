#include "ds/linked_list.h"

#include <memory.h>

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
sllDelete(SLinkedList* sll)
{
    assert(sll != NULL);

    while (sllDeleteHead(sll) == WIM_TRUE) continue;

    sll->head       = NULL;
    sll->tail       = NULL;
    sll->node_count = 0;
}

void 
sllPrepend(SLinkedList* sll, void* data, u64 data_size)
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

void 
sllAppend(SLinkedList* sll, void* data, u64 data_size)
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

void 
sllInsert(SLinkedList* sll, void* data, u64 data_size, u64 index)
{
    assert(sll  != NULL);
    assert(data != NULL);
    
    if (sll->head == NULL || index == 0)    { sllPrepend(sll, data, data_size); return; }
    if (index >= sll->node_count)           { sllAppend(sll, data, data_size); return; }

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