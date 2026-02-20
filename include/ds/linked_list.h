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

void    sllPrepend(SLinkedList* sll, void* data, u64 data_size);
b8      sllDeleteHead(SLinkedList* sll);

void    sllAppend(SLinkedList* sll, void* data, u64 data_size);
b8      sllDeleteTail(SLinkedList* sll);

void    sllInsert(SLinkedList* sll, void* data, u64 data_size, u64 index);
b8      sllDeleteAt(SLinkedList* sll, u64 index);

u64 sllGetNodeCount(SLinkedList* sll);

#define forEachSLLNode(sll, node) \
    for ((node) = (sll)->head; (node) != NULL; (node) = (node)->next)

// Double Linked List Node
typedef struct DLLNode
{
    void*           data;
    struct DLLNode* left;
    struct DLLNode* right;
} DLLNode;

// Circular Linked List Node
typedef struct CLLNode
{
    void*           data;
    struct CLLNode* left;
    struct CLLNode* right;
} CLLNode;

#endif // WIM_LINKED_LIST_H