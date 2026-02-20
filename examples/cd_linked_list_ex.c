#include <stdio.h>
#include "ds/linked_list.h"

void printCDLLForward(CDLinkedList* cdll)
{
    DLLNode* node = NULL;
    u64 i = 0;
    printf("Forward  (%lu nodes): ", cdll->node_count);
    if (cdll->node_count == 0) { printf("EMPTY\n"); return; }
    forEachCDLLNodeForward(cdll, node, i)
    {
        printf("%d <-> ", *(int*)node->data);
    }
    printf("(back to head: %d)\n", *(int*)cdll->head->data);
}

void printCDLLBackward(CDLinkedList* cdll)
{
    DLLNode* node = NULL;
    u64 i = 0;
    printf("Backward (%lu nodes): ", cdll->node_count);
    if (cdll->node_count == 0) { printf("EMPTY\n"); return; }
    forEachCDLLNodeBackward(cdll, node, i)
    {
        printf("%d <-> ", *(int*)node->data);
    }
    printf("(back to tail: %d)\n", *(int*)cdll->tail->data);
}

void printBoth(CDLinkedList* cdll)
{
    printCDLLForward(cdll);
    printCDLLBackward(cdll);
    printf("\n");
}

int main(void)
{
    CDLinkedList cdll = cdllCreate();

    // Build initial list via tail inserts
    int a = 10, b = 20, c = 30, d = 40;
    cdllInsertTail(&cdll, &a, sizeof(int));
    cdllInsertTail(&cdll, &b, sizeof(int));
    cdllInsertTail(&cdll, &c, sizeof(int));
    cdllInsertTail(&cdll, &d, sizeof(int));
    printf("-- Initial list --\n");
    printBoth(&cdll); // 10 <-> 20 <-> 30 <-> 40

    // Prepend
    int e = 5;
    cdllInsertHead(&cdll, &e, sizeof(int));
    printf("-- After InsertHead (5) --\n");
    printBoth(&cdll); // 5 <-> 10 <-> 20 <-> 30 <-> 40

    // Insert at index 2 (iterates from head)
    int f = 15;
    cdllInsertAt(&cdll, &f, sizeof(int), 2);
    printf("-- After InsertAt index 2 (15) --\n");
    printBoth(&cdll); // 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> 40

    // Insert at index 5 (iterates from tail)
    int g = 35;
    cdllInsertAt(&cdll, &g, sizeof(int), 5);
    printf("-- After InsertAt index 5 (35) --\n");
    printBoth(&cdll); // 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> 35 <-> 40

    // Delete head
    cdllDeleteHead(&cdll);
    printf("-- After DeleteHead --\n");
    printBoth(&cdll); // 10 <-> 15 <-> 20 <-> 30 <-> 35 <-> 40

    // Delete tail
    cdllDeleteTail(&cdll);
    printf("-- After DeleteTail --\n");
    printBoth(&cdll); // 10 <-> 15 <-> 20 <-> 30 <-> 35

    // Delete at index 1 (iterates from head)
    cdllDeleteAt(&cdll, 1);
    printf("-- After DeleteAt index 1 --\n");
    printBoth(&cdll); // 10 <-> 20 <-> 30 <-> 35

    // Delete at index 3 (iterates from tail)
    cdllDeleteAt(&cdll, 3);
    printf("-- After DeleteAt index 3 --\n");
    printBoth(&cdll); // 10 <-> 20 <-> 30

    // Delete until empty
    cdllDeleteHead(&cdll);
    cdllDeleteHead(&cdll);
    cdllDeleteHead(&cdll);
    printf("-- After deleting all nodes --\n");
    printBoth(&cdll); // EMPTY

    cdllDelete(&cdll);
    return 0;
}