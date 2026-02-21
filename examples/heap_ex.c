#include <stdio.h>
#include "ds/heap.h"

// Max heap comparator - returns true if a < b (so larger values bubble up)
b8 maxComparator(void* a, void* b)
{
    return *(int*)a < *(int*)b;
}

// Min heap comparator - returns true if a > b (so smaller values bubble up)
b8 minComparator(void* a, void* b)
{
    return *(int*)a > *(int*)b;
}

void printHeap(Heap* heap, const char* label)
{
    printf("%s (size: %lu): [ ", label, heapSize(heap));
    for (u64 i = 0; i < heapSize(heap); i++)
    {
        printf("%d ", *(int*)daGet(&heap->da, i));
    }
    printf("]\n");
}

int main(void)
{
    // --- Max Heap ---
    printf("=== Max Heap ===\n\n");
    Heap max_heap = heapCreate(sizeof(int), 8, maxComparator);

    int values[] = { 30, 10, 50, 20, 40 };
    for (int i = 0; i < 5; i++)
    {
        heapInsert(&max_heap, &values[i]);
        printHeap(&max_heap, "After insert");
    }
    printf("\n");

    // Extract all - should come out in descending order
    printf("-- Extracting all (should be descending) --\n");
    while (heapIsEmpty(&max_heap) == WIM_FALSE)
    {
        int out = 0;
        heapExtract(&max_heap, &out);
        printf("Extracted: %d\n", out);
    }
    printHeap(&max_heap, "After extracting all");
    heapDestroy(&max_heap);

    // --- Min Heap ---
    printf("\n=== Min Heap ===\n\n");
    Heap min_heap = heapCreate(sizeof(int), 8, minComparator);

    for (int i = 0; i < 5; i++)
    {
        heapInsert(&min_heap, &values[i]);
        printHeap(&min_heap, "After insert");
    }
    printf("\n");

    // Extract all - should come out in ascending order
    printf("-- Extracting all (should be ascending) --\n");
    while (heapIsEmpty(&min_heap) == WIM_FALSE)
    {
        int out = 0;
        heapExtract(&min_heap, &out);
        printf("Extracted: %d\n", out);
    }
    printHeap(&min_heap, "After extracting all");
    heapDestroy(&min_heap);

    // --- Heap sort ---
    printf("\n=== Heap Sort (ascending) ===\n\n");
    Heap sort_heap = heapCreate(sizeof(int), 8, minComparator);

    int unsorted[] = { 15, 3, 78, 42, 6, 91, 27 };
    u64 count = sizeof(unsorted) / sizeof(unsorted[0]);

    printf("Unsorted: [ ");
    for (u64 i = 0; i < count; i++)
    {
        printf("%d ", unsorted[i]);
        heapInsert(&sort_heap, &unsorted[i]);
    }
    printf("]\n");

    printf("Sorted:   [ ");
    while (heapIsEmpty(&sort_heap) == WIM_FALSE)
    {
        int out = 0;
        heapExtract(&sort_heap, &out);
        printf("%d ", out);
    }
    printf("]\n");

    heapDestroy(&sort_heap);
    return 0;
}