#include <stdio.h>
#include "ds/dynamic_array.h"

int main(void)
{
    DynamicArray da = daCreate(sizeof(int), 8);

    // Push some values
    for (int i = 0; i < 5; i++)
        daPushBack(&da, &i);

    // Print all values
    for (u64 i = 0; i < daGetSize(&da); i++)
        printf("%d\n", *(int*)daGet(&da, i));

    // Update a value
    int new_val = 99;
    daSet(&da, 2, &new_val);

    // Insert at index 1
    int inserted = 42;
    daInsertAt(&da, &inserted, 1);

    // Delete at index 3
    daDeleteAt(&da, 3);

    // Pop the last element
    daPopBack(&da);

    daDestroy(&da);
    return 0;
}