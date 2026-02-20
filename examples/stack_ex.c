#include <stdio.h>
#include "ds/stack.h"

void printStack(Stack* s)
{
    printf("Stack (size: %lu): ", stackSize(s));
    if (stackIsEmpty(s)) { printf("EMPTY\n"); return; }
    printf("bottom [ ");
    for (u64 i = 0; i < stackSize(s); i++)
    {
        printf("%d ", *(int*)daGet(&s->da, i));
    }
    printf("] top (peek: %d)\n", *(int*)stackPeek(s));
}

int main(void)
{
    // --- Dynamic stack (grows as needed) ---
    printf("=== Dynamic Stack ===\n\n");
    Stack dynamic = stackCreate(sizeof(int), 4, WIM_FALSE);

    int a = 10, b = 20, c = 30, d = 40;
    stackPush(&dynamic, &a);
    stackPush(&dynamic, &b);
    stackPush(&dynamic, &c);
    stackPush(&dynamic, &d);
    printf("-- After pushing 10, 20, 30, 40 --\n");
    printStack(&dynamic); // bottom [ 10 20 30 40 ] top (peek: 40)

    // Push beyond initial capacity to verify dynamic growth
    int e = 50, f = 60;
    stackPush(&dynamic, &e);
    stackPush(&dynamic, &f);
    printf("-- After pushing 50, 60 (beyond initial capacity) --\n");
    printStack(&dynamic); // bottom [ 10 20 30 40 50 60 ] top (peek: 60)

    // Pop
    int out = 0;
    stackPop(&dynamic, &out);
    printf("-- After Pop (got: %d) --\n", out);
    printStack(&dynamic); // bottom [ 10 20 30 40 50 ] top (peek: 50)

    // Peek
    printf("-- Peek: %d --\n\n", *(int*)stackPeek(&dynamic));

    // Clear
    stackClear(&dynamic);
    printf("-- After Clear --\n");
    printStack(&dynamic); // EMPTY

    // Pop on empty (should not crash)
    stackPop(&dynamic, &out);
    printf("-- Pop on empty stack (should be safe) --\n");
    printStack(&dynamic); // EMPTY

    stackDestroy(&dynamic);

    // --- Static stack (fixed capacity) ---
    printf("\n=== Static Stack ===\n\n");
    Stack static_s = stackCreate(sizeof(int), 3, WIM_TRUE);

    int x = 1, y = 2, z = 3, w = 4;
    stackPush(&static_s, &x);
    stackPush(&static_s, &y);
    stackPush(&static_s, &z);
    printf("-- After pushing 1, 2, 3 (at capacity) --\n");
    printStack(&static_s); // bottom [ 1 2 3 ] top (peek: 3)

    // Push beyond capacity (should be silently ignored)
    stackPush(&static_s, &w);
    printf("-- After pushing 4 (beyond capacity, should be ignored) --\n");
    printStack(&static_s); // bottom [ 1 2 3 ] top (peek: 3)

    stackDestroy(&static_s);
    return 0;
}