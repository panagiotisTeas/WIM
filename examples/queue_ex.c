#include <stdio.h>
#include "ds/queue.h"

void printQueue(Queue* q)
{
    printf("Queue (size: %lu / capacity: %lu): ", qSize(q), q->capacity);
    if (qIsEmpty(q)) { printf("EMPTY\n"); return; }
    printf("front [ ");
    SLLNode* node = NULL;
    forEachSLLNode(&q->sll, node)
    {
        printf("%d ", *(int*)node->data);
    }
    printf("] back (peek: %d)\n", *(int*)qPeek(q));
}

int main(void)
{
    // --- Bounded queue ---
    printf("=== Bounded Queue (capacity: 4) ===\n\n");
    Queue bounded = qCreate(4);

    int a = 10, b = 20, c = 30, d = 40;
    qEnqueue(&bounded, &a, sizeof(int));
    qEnqueue(&bounded, &b, sizeof(int));
    qEnqueue(&bounded, &c, sizeof(int));
    qEnqueue(&bounded, &d, sizeof(int));
    printf("-- After enqueuing 10, 20, 30, 40 --\n");
    printQueue(&bounded); // front [ 10 20 30 40 ] back (peek: 10)

    // Enqueue beyond capacity (should be silently ignored)
    int e = 50;
    qEnqueue(&bounded, &e, sizeof(int));
    printf("-- After enqueuing 50 (beyond capacity, should be ignored) --\n");
    printQueue(&bounded); // front [ 10 20 30 40 ] back (peek: 10)

    // Dequeue
    int out = 0;
    qDequeue(&bounded, &out, sizeof(int));
    printf("-- After Dequeue (got: %d) --\n", out);
    printQueue(&bounded); // front [ 20 30 40 ] back (peek: 20)

    // Peek
    printf("-- Peek: %d --\n\n", *(int*)qPeek(&bounded));

    // Now there's room again
    qEnqueue(&bounded, &e, sizeof(int));
    printf("-- After enqueuing 50 (slot freed up) --\n");
    printQueue(&bounded); // front [ 20 30 40 50 ] back (peek: 20)

    // Clear
    qClear(&bounded);
    printf("-- After Clear --\n");
    printQueue(&bounded); // EMPTY

    // Dequeue on empty (should not crash)
    qDequeue(&bounded, &out, sizeof(int));
    printf("-- Dequeue on empty (should be safe) --\n");
    printQueue(&bounded); // EMPTY

    qDestroy(&bounded);

    return 0;
}