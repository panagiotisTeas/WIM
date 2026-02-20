#include <stdio.h>
#include "ds/linked_list.h"

void printList(SLinkedList* sll)
{
    SLLNode* node = NULL;
    printf("List (%lu nodes): ", sll->node_count);
    forEachSLLNode(sll, node)
    {
        printf("%d -> ", *(int*)node->data);
    }
    printf("NULL\n");
}

int main(void)
{
    SLinkedList sll = sllCreate();

    // Append some values
    int a = 10, b = 20, c = 30;
    sllAppend(&sll, &a, sizeof(int));
    sllAppend(&sll, &b, sizeof(int));
    sllAppend(&sll, &c, sizeof(int));
    printList(&sll); // 10 -> 20 -> 30 -> NULL

    // Prepend a value
    int d = 5;
    sllPrepend(&sll, &d, sizeof(int));
    printList(&sll); // 5 -> 10 -> 20 -> 30 -> NULL

    // Insert in the middle at index 2
    int e = 15;
    sllInsert(&sll, &e, sizeof(int), 2);
    printList(&sll); // 5 -> 10 -> 15 -> 20 -> 30 -> NULL

    // Delete head
    sllDeleteHead(&sll);
    printList(&sll); // 10 -> 15 -> 20 -> 30 -> NULL

    // Delete tail
    sllDeleteTail(&sll);
    printList(&sll); // 10 -> 15 -> 20 -> NULL

    // Delete at index 1
    sllDeleteAt(&sll, 1);
    printList(&sll); // 10 -> 20 -> NULL

    // Clean up
    sllDelete(&sll);
    printList(&sll); // (empty)

    return 0;
}