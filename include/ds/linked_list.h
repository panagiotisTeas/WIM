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
void        dllDelete(DLinkedList* dll);

void    dllInsertHead(DLinkedList* dll, void* data, u64 data_size);
b8      dllDeleteHead(DLinkedList* dll);

void    dllInsertTail(DLinkedList* dll, void* data, u64 data_size);
b8      dllDeleteTail(DLinkedList* dll);

void    dllInsertAt(DLinkedList* dll, void* data, u64 data_size, u64 index);
b8      dllDeleteAt(DLinkedList* dll, u64 index);

u64 dllGetNodeCount(DLinkedList* dll);

#define forEachDLLNodeForward(dll, node) \
    for ((node) = (dll)->head; (node) != NULL; (node) = (node)->next)

#define forEachDLLNodeBackward(dll, node) \
    for ((node) = (dll)->tail; (node) != NULL; (node) = (node)->prev)

// Circular Single Linked List API

CSLinkedList    csllCreate(void);
void            csllDelete(CSLinkedList* csll);

void    csllInsertHead(CSLinkedList* csll, void* data, u64 data_size);
b8      csllDeleteHead(CSLinkedList* csll);

void    csllInsertTail(CSLinkedList* csll, void* data, u64 data_size);
b8      csllDeleteTail(CSLinkedList* csll);

void    csllInsertAt(CSLinkedList* csll, void* data, u64 data_size, u64 index);
b8      csllDeleteAt(CSLinkedList* csll, u64 index);

u64 csllGetNodeCount(CSLinkedList* csll);

#define forEachCSLLNode(csll, node, i) \
    for ((node) = (csll)->head, (i) = 0; (i) < (csll)->node_count; (node) = (node)->next, (i)++)

// Circular Double Linked List API

CDLinkedList    cdllCreate(void);
void            cdllDelete(CDLinkedList* cdll);

void    cdllInsertHead(CDLinkedList* cdll, void* data, u64 data_size);
b8      cdllDeleteHead(CDLinkedList* cdll);

void    cdllInsertTail(CDLinkedList* cdll, void* data, u64 data_size);
b8      cdllDeleteTail(CDLinkedList* cdll);

void    cdllInsertAt(CDLinkedList* cdll, void* data, u64 data_size, u64 index);
b8      cdllDeleteAt(CDLinkedList* cdll, u64 index);

u64 cdllGetNodeCount(CDLinkedList* cdll);

#define forEachCDLLNodeForward(cdll, node, i) \
    for ((node) = (cdll)->head, (i) = 0; (i) < (cdll)->node_count; (node) = (node)->next, (i)++)

#define forEachCDLLNodeBackward(cdll, node, i) \
    for ((node) = (cdll)->tail, (i) = 0; (i) < (cdll)->node_count; (node) = (node)->prev, (i)++)

#endif // WIM_LINKED_LIST_H