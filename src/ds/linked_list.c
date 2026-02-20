#include "ds/linked_list.h"

#include <memory.h>

// --------------------------
// --- Single Linked Node ---
// --------------------------

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

// --------------------------
// --- Double Linked Node ---
// --------------------------

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

// --------------------------
// --- Single Linked List ---
// --------------------------

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

// --------------------------
// --- Double Linked List ---
// --------------------------

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

// -----------------------------------
// --- Circular Single Linked List ---
// -----------------------------------

CSLinkedList    
csllCreate(void)
{
    CSLinkedList csll = (CSLinkedList){
        .head       = NULL,
        .tail       = NULL,
        .node_count = 0
    };

    return csll;
}

void            
csllDelete(CSLinkedList* csll)
{
    assert(csll != NULL);

    while (csllDeleteHead(csll) == WIM_TRUE) continue;

    csll->head       = NULL;
    csll->tail       = NULL;
    csll->node_count = 0;
}

void    
csllInsertHead(CSLinkedList* csll, void* data, u64 data_size)
{
    assert(csll  != NULL);
    assert(data != NULL);

    SLLNode* node = sllNodeCreate(data, data_size);
    if (csll->node_count == 0)
    {
        csll->head = node;
        csll->tail = node;
        node->next = node;
    }
    else
    {
        node->next          = csll->head;
        csll->head          = node;
        csll->tail->next    = csll->head;
    }

    csll->node_count++;
}

b8      
csllDeleteHead(CSLinkedList* csll)
{
    assert(csll != NULL);
    
    if (csll->node_count == 0) return WIM_FALSE;

    SLLNode* new_head = csll->head->next;
    sllNodeDestroy(csll->head);

    csll->node_count--;

    if (csll->node_count == 0) {csll->tail = NULL; csll->head = NULL; return WIM_TRUE; };

    csll->head          = new_head;
    csll->tail->next    = csll->head;

    return WIM_TRUE;
}

void    
csllInsertTail(CSLinkedList* csll, void* data, u64 data_size)
{
    assert(csll != NULL);
    assert(data != NULL);

    SLLNode* node = sllNodeCreate(data, data_size);
    if (csll->node_count == 0)
    {
        csll->head = node;
        csll->tail = node;
        node->next = node;
    }
    else
    {
        csll->tail->next    = node;
        node->next          = csll->head;
        csll->tail          = node;
    }

    csll->node_count++;
}

b8      
csllDeleteTail(CSLinkedList* csll)
{
    assert(csll != NULL);
    
    if (csll->node_count == 0) return WIM_FALSE;
    if (csll->node_count == 1) return csllDeleteHead(csll);

    SLLNode* tmp = csll->head;
    // SLLNode* prev = NULL;

    while (tmp->next->next != csll->head)
    {
        // prev    = tmp;
        tmp = tmp->next;
    }

    sllNodeDestroy(tmp->next);
    tmp->next  = csll->head;
    csll->tail = tmp;
    csll->node_count--;

    return WIM_TRUE;
}

void    
csllInsertAt(CSLinkedList* csll, void* data, u64 data_size, u64 index)
{
    assert(csll != NULL);
    assert(data != NULL);
    
    if (csll->head == NULL || index == 0)   { csllInsertHead(csll, data, data_size); return; }
    if (index >= csll->node_count)           { csllInsertTail(csll, data, data_size); return; }

    SLLNode* tmp = csll->head;
    while (index > 1)
    {
        tmp = tmp->next;
        index--;
    }

    SLLNode* node   = sllNodeCreate(data, data_size);
    node->next      = tmp->next;
    tmp->next       = node;

    csll->node_count++;
}

b8      
csllDeleteAt(CSLinkedList* csll, u64 index)
{
    assert(csll != NULL);

    if (csll->node_count == 0)          return WIM_FALSE;
    if (index == 0)                     return csllDeleteHead(csll);
    if (index >= csll->node_count - 1)  return csllDeleteTail(csll);

    SLLNode* tmp    = csll->head;
    SLLNode* prev   = NULL;
    while (index > 0)
    {
        prev    = tmp;
        tmp     = tmp->next;
        index--;
    }

    prev->next = tmp->next;

    sllNodeDestroy(tmp);
    csll->node_count--;

    return WIM_TRUE;
}

u64 
csllGetNodeCount(CSLinkedList* csll)
{
    return csll->node_count;
}

// -----------------------------------
// --- Circular Double Linked List ---
// -----------------------------------

CDLinkedList    
cdllCreate(void)
{
    CDLinkedList cdll = (CDLinkedList){
        .head       = NULL,
        .tail       = NULL,
        .node_count = 0
    };

    return cdll;
}

void            
cdllDelete(CDLinkedList* cdll)
{
    assert(cdll != NULL);

    while (cdllDeleteHead(cdll) == WIM_TRUE) continue;

    cdll->head       = NULL;
    cdll->tail       = NULL;
    cdll->node_count = 0;
}

void    
cdllInsertHead(CDLinkedList* cdll, void* data, u64 data_size)
{
    assert(cdll != NULL);
    assert(data != NULL);

    DLLNode* node = dllNodeCreate(data, data_size);
    if (cdll->node_count == 0)
    {
        cdll->head  = node;
        cdll->tail  = node;
        node->next  = node;
        node->prev  = node;
    }
    else
    {
        node->next          = cdll->head;
        node->prev          = cdll->tail;
        cdll->head->prev    = node;
        cdll->tail->next    = node;
        cdll->head          = node;
    }

    cdll->node_count++;
}

b8      
cdllDeleteHead(CDLinkedList* cdll)
{
    assert(cdll != NULL);

    if (cdll->node_count == 0) return WIM_FALSE;

    DLLNode* new_head = cdll->head->next;
    dllNodeDestroy(cdll->head);
    cdll->node_count--;

    if (cdll->node_count == 0) { cdll->head = NULL; cdll->tail = NULL; return WIM_TRUE; }

    cdll->head          = new_head;
    cdll->head->prev    = cdll->tail;
    cdll->tail->next    = cdll->head;

    return WIM_TRUE;
}

void    
cdllInsertTail(CDLinkedList* cdll, void* data, u64 data_size)
{
    assert(cdll != NULL);
    assert(data != NULL);

    DLLNode* node = dllNodeCreate(data, data_size);
    if (cdll->node_count == 0)
    {
        cdll->head  = node;
        cdll->tail  = node;
        node->next  = node;
        node->prev  = node;
    }
    else
    {
        node->prev          = cdll->tail;
        node->next          = cdll->head;
        cdll->tail->next    = node;
        cdll->head->prev    = node;
        cdll->tail          = node;
    }
    cdll->node_count++;
}

b8      
cdllDeleteTail(CDLinkedList* cdll)
{
    assert(cdll != NULL);

    if (cdll->node_count == 0) return WIM_FALSE;
    if (cdll->node_count == 1) return cdllDeleteHead(cdll);

    DLLNode* new_tail = cdll->tail->prev;
    dllNodeDestroy(cdll->tail);
    cdll->tail          = new_tail;
    cdll->tail->next    = cdll->head;
    cdll->head->prev    = cdll->tail;
    cdll->node_count--;

    return WIM_TRUE;
}

void    
cdllInsertAt(CDLinkedList* cdll, void* data, u64 data_size, u64 index)
{
    assert(cdll != NULL);
    assert(data != NULL);

    if (cdll->head == NULL || index == 0)   { cdllInsertHead(cdll, data, data_size); return; }
    if (index >= cdll->node_count)          { cdllInsertTail(cdll, data, data_size); return; }

    DLLNode* tmp = NULL;
    if (index <= cdll->node_count / 2)
    {
        tmp = cdll->head;
        while (index > 1) { tmp = tmp->next; index--; }
    }
    else
    {
        u64 reverse_index = cdll->node_count - index;
        tmp = cdll->tail;
        while (reverse_index > 0) { tmp = tmp->prev; reverse_index--; }
    }

    DLLNode* node   = dllNodeCreate(data, data_size);
    node->next      = tmp->next;
    node->prev      = tmp;
    tmp->next->prev = node;
    tmp->next       = node;

    cdll->node_count++;
}

b8      
cdllDeleteAt(CDLinkedList* cdll, u64 index)
{
    assert(cdll != NULL);
    
    if (cdll->node_count == 0)          return WIM_FALSE;
    if (index == 0)                     return cdllDeleteHead(cdll);
    if (index >= cdll->node_count - 1)  return cdllDeleteTail(cdll);

    DLLNode* tmp = NULL;
    if (index <= cdll->node_count / 2)
    {
        tmp = cdll->head;
        while (index > 0) { tmp = tmp->next; index--; }
    }
    else
    {
        u64 reverse_index = (cdll->node_count - 1) - index;
        tmp = cdll->tail;
        while (reverse_index > 0) { tmp = tmp->prev; reverse_index--; }
    }

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    dllNodeDestroy(tmp);
    cdll->node_count--;

    return WIM_TRUE;
}

u64 cdllGetNodeCount(CDLinkedList* cdll)
{
    return cdll->node_count;
}