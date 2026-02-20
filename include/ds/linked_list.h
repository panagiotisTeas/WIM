#ifndef WIM_LINKED_LIST_H
#define WIM_LINKED_LIST_H

#include "common.h"

// Single Linked List Node
typedef struct SLLNode
{
    void*           data;
    struct SLLNode* next;
} SLLNode;

// Single Linked List
typedef struct SLinkedList
{
    SLLNode*    head;
    SLLNode*    tail;
    u64         node_count;
} SLinkedList;

SLLNode*    sllNodeCreate(void* data, u64 data_size); 
void        sllNodeDestroy(SLLNode* node);

SLinkedList sllCreate(void);
void        sllDelete(SLinkedList* sll);

void    sllInsertHead(SLinkedList* sll, void* data, u64 data_size);
b8      sllDeleteHead(SLinkedList* sll);

void    sllInsertTail(SLinkedList* sll, void* data, u64 data_size);
b8      sllDeleteTail(SLinkedList* sll);

void    sllInsertAt(SLinkedList* sll, void* data, u64 data_size, u64 index);
b8      sllDeleteAt(SLinkedList* sll, u64 index);

u64 sllGetNodeCount(SLinkedList* sll);

#define forEachSLLNode(sll, node) \
    for ((node) = (sll)->head; (node) != NULL; (node) = (node)->next)

// Double Linked List Node
typedef struct DLLNode
{
    void*           data;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

// Double Linked List
typedef struct DLinkedList
{
    DLLNode*    head;
    DLLNode*    tail;
    u64         node_count;
} DLinkedList;

DLLNode*    dllNodeCreate(void* data, u64 data_size); 
void        dllNodeDestroy(DLLNode* node);

DLinkedList dllCreate(void);
void        dllDelete(DLinkedList* sll);

void    dllInsertHead(DLinkedList* sll, void* data, u64 data_size);
b8      dllDeleteHead(DLinkedList* sll);

void    dllInsertTail(DLinkedList* sll, void* data, u64 data_size);
b8      dllDeleteTail(DLinkedList* sll);

void    dllInsertAt(DLinkedList* sll, void* data, u64 data_size, u64 index);
b8      dllDeleteAt(DLinkedList* sll, u64 index);

u64 dllGetNodeCount(DLinkedList* sll);

#define forEachDLLNodeForward(dll, node) \
    for ((node) = (dll)->head; (node) != NULL; (node) = (node)->next)

#define forEachDLLNodeBackward(dll, node) \
    for ((node) = (dll)->tail; (node) != NULL; (node) = (node)->prev)

// Circular Linked List Node
typedef struct CLLNode
{
    void*           data;
    struct CLLNode* left;
    struct CLLNode* right;
} CLLNode;

#endif // WIM_LINKED_LIST_H