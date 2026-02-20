#include <stdio.h>
#include "ds/linked_list.h"

void printCSLL(CSLinkedList* csll)
{
    SLLNode* node = NULL;
    u64 i = 0;
    printf("CSLL (%lu nodes): ", csll->node_count);
    if (csll->node_count == 0) { printf("EMPTY\n"); return; }
    forEachCSLLNode(csll, node, i)
    {
        printf("%d -> ", *(int*)node->data);
    }
    printf("(back to head: %d)\n", *(int*)csll->head->data);
}

int main(void)
{
    CSLinkedList csll = csllCreate();

    // Build initial list via tail inserts
    int a = 10, b = 20, c = 30, d = 40;
    csllInsertTail(&csll, &a, sizeof(int));
    csllInsertTail(&csll, &b, sizeof(int));
    csllInsertTail(&csll, &c, sizeof(int));
    csllInsertTail(&csll, &d, sizeof(int));
    printf("-- Initial list --\n");
    printCSLL(&csll); // 10 -> 20 -> 30 -> 40 -> (back to head: 10)

    // Prepend
    int e = 5;
    csllInsertHead(&csll, &e, sizeof(int));
    printf("-- After InsertHead (5) --\n");
    printCSLL(&csll); // 5 -> 10 -> 20 -> 30 -> 40 -> (back to head: 5)

    // Insert at index 2
    int f = 15;
    csllInsertAt(&csll, &f, sizeof(int), 2);
    printf("-- After InsertAt index 2 (15) --\n");
    printCSLL(&csll); // 5 -> 10 -> 15 -> 20 -> 30 -> 40 -> (back to head: 5)

    // Delete head
    csllDeleteHead(&csll);
    printf("-- After DeleteHead --\n");
    printCSLL(&csll); // 10 -> 15 -> 20 -> 30 -> 40 -> (back to head: 10)

    // Delete tail
    csllDeleteTail(&csll);
    printf("-- After DeleteTail --\n");
    printCSLL(&csll); // 10 -> 15 -> 20 -> 30 -> (back to head: 10)

    // Delete at index 1
    csllDeleteAt(&csll, 1);
    printf("-- After DeleteAt index 1 --\n");
    printCSLL(&csll); // 10 -> 20 -> 30 -> (back to head: 10)

    // Delete until empty
    csllDeleteHead(&csll);
    csllDeleteHead(&csll);
    csllDeleteHead(&csll);
    printf("-- After deleting all nodes --\n");
    printCSLL(&csll); // EMPTY

    csllDelete(&csll);
    return 0;
}