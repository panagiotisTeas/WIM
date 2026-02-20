#include <stdio.h>
#include "ds/linked_list.h"

void printForward(DLinkedList* dll)
{
    DLLNode* node = NULL;
    printf("Forward  (%lu nodes): NULL <-> ", dll->node_count);
    forEachDLLNodeForward(dll, node)
    {
        printf("%d <-> ", *(int*)node->data);
    }
    printf("NULL\n");
}

void printBackward(DLinkedList* dll)
{
    DLLNode* node = NULL;
    printf("Backward (%lu nodes): NULL <-> ", dll->node_count);
    forEachDLLNodeBackward(dll, node)
    {
        printf("%d <-> ", *(int*)node->data);
    }
    printf("NULL\n");
}

void printBoth(DLinkedList* dll)
{
    printForward(dll);
    printBackward(dll);
    printf("\n");
}

int main(void)
{
    DLinkedList dll = dllCreate();

    // Build an initial list via tail inserts
    int a = 10, b = 20, c = 30, d = 40;
    dllInsertTail(&dll, &a, sizeof(int));
    dllInsertTail(&dll, &b, sizeof(int));
    dllInsertTail(&dll, &c, sizeof(int));
    dllInsertTail(&dll, &d, sizeof(int));
    printf("-- Initial list --\n");
    printBoth(&dll); // 10 <-> 20 <-> 30 <-> 40

    // Prepend
    int e = 5;
    dllInsertHead(&dll, &e, sizeof(int));
    printf("-- After InsertHead (5) --\n");
    printBoth(&dll); // 5 <-> 10 <-> 20 <-> 30 <-> 40

    // Insert at index 2 (close to head, iterates forward)
    int f = 15;
    dllInsertAt(&dll, &f, sizeof(int), 2);
    printf("-- After InsertAt index 2 (15) --\n");
    printBoth(&dll); // 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> 40

    // Insert at index 5 (close to tail, iterates backward)
    int g = 35;
    dllInsertAt(&dll, &g, sizeof(int), 5);
    printf("-- After InsertAt index 5 (35) --\n");
    printBoth(&dll); // 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> 35 <-> 40

    // Delete head
    dllDeleteHead(&dll);
    printf("-- After DeleteHead --\n");
    printBoth(&dll); // 10 <-> 15 <-> 20 <-> 30 <-> 35 <-> 40

    // Delete tail
    dllDeleteTail(&dll);
    printf("-- After DeleteTail --\n");
    printBoth(&dll); // 10 <-> 15 <-> 20 <-> 30 <-> 35

    // Delete at index 1 (close to head, iterates forward)
    dllDeleteAt(&dll, 1);
    printf("-- After DeleteAt index 1 --\n");
    printBoth(&dll); // 10 <-> 20 <-> 30 <-> 35

    // Delete at index 3 (close to tail, iterates backward)
    dllDeleteAt(&dll, 3);
    printf("-- After DeleteAt index 3 --\n");
    printBoth(&dll); // 10 <-> 20 <-> 30

    // Clean up
    dllDelete(&dll);
    printf("-- After Delete --\n");
    printBoth(&dll); // empty

    return 0;
}