#ifndef WIM_LINKED_LIST_H
#define WIM_LINKED_LIST_H

#include "common.h"

// Single Linked Node
typedef struct SLLNode
{
    void*           data;
    struct SLLNode* next;
} SLLNode;

// Double Linked Node
typedef struct DLLNode
{
    void*           data;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

// Single Linked List
typedef struct SLinkedList
{
    SLLNode*    head;
    SLLNode*    tail;
    u64         node_count;
} SLinkedList;

// Double Linked List
typedef struct DLinkedList
{
    DLLNode*    head;
    DLLNode*    tail;
    u64         node_count;
} DLinkedList;

typedef SLinkedList CSLinkedList;    // Circular Single Linked List
typedef DLinkedList CDLinkedList;    // Circular Double Linked List

// Single Linked Nodes API

SLLNode*    sllNodeCreate(void* data, u64 data_size); 
void        sllNodeDestroy(SLLNode* node);

// Double Linked Nodes API

DLLNode*    dllNodeCreate(void* data, u64 data_size); 
void        dllNodeDestroy(DLLNode* node);

// Single Linked List API

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

// Double Linked List API

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

// Circular Single Linked List API

CSLinkedList    csllCreate(void);
void            csllDelete(CSLinkedList* sll);

void    csllInsertHead(CSLinkedList* sll, void* data, u64 data_size);
b8      csllDeleteHead(CSLinkedList* sll);

void    csllInsertTail(CSLinkedList* sll, void* data, u64 data_size);
b8      csllDeleteTail(CSLinkedList* sll);

void    csllInsertAt(CSLinkedList* sll, void* data, u64 data_size, u64 index);
b8      csllDeleteAt(CSLinkedList* sll, u64 index);

u64 csllGetNodeCount(CSLinkedList* sll);

#define forEachCSLLNode(csll, node, index) \
    for ((node) = (csll)->head, (i) = 0; (i) < (csll)->node_count; (node) = (node)->next, (i)++)

// Circular Double Linked List API

CDLinkedList    cdllCreate(void);
void            cdllDelete(CDLinkedList* sll);

void    cdllInsertHead(CDLinkedList* sll, void* data, u64 data_size);
b8      cdllDeleteHead(CDLinkedList* sll);

void    cdllInsertTail(CDLinkedList* sll, void* data, u64 data_size);
b8      cdllDeleteTail(CDLinkedList* sll);

void    cdllInsertAt(CDLinkedList* sll, void* data, u64 data_size, u64 index);
b8      cdllDeleteAt(CDLinkedList* sll, u64 index);

u64 cdllGetNodeCount(CDLinkedList* sll);

#define forEachCDLLNodeForward(cdll, node) \
    for ((node) = (cdll)->head, (i) = 0; (i) < (cdll)->node_count; (node) = (node)->next, (i)++)

#define forEachCDLLNodeBackward(cdll, node) \
    for ((node) = (cdll)->tail, (i) = 0; (i) < (cdll)->node_count; (node) = (node)->prev, (i)++)
    
#endif // WIM_LINKED_LIST_H