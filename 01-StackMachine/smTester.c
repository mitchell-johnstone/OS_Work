#include <stdio.h>
#include "stackm.c"

int main() {
    stackm mystack;
    smInit(&mystack);

    smPush(&mystack, 2);
    smPush(&mystack, 3);
    smPush(&mystack, 4);
    smPrint(&mystack);

    smPop(&mystack);
    smPrint(&mystack);
    smAdd(&mystack);
    smPrint(&mystack);

    int value = 0;
    smTop(&mystack, &value);
    printf("%d\n", value);

    smPush(&mystack, 10);
    smPush(&mystack, 11);
    smPrint(&mystack);
    smMult(&mystack);
    smPrint(&mystack);

    smPush(&mystack, 10);
    smPush(&mystack, 11);
    smPrint(&mystack);
    smRotate(&mystack, 5);
    smPrint(&mystack);

    smClear(&mystack);
    smPrint(&mystack);
    return 0;
}
