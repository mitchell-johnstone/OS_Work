#include <stdio.h>
#include "stackm.c"

void doPush(stackm* s, int v)
{
	printf("Push Ret: %d\n", smPush(s, v));
}

int main() {
	stackm mystack;
	smInit(&mystack);
	doPush(&mystack, 1);
	doPush(&mystack, 2);
	doPush(&mystack, 3);
	printf("SIZE: %d\n", smSize(&mystack));
	smClear(&mystack);
	printf("SIZE: %d\n", smSize(&mystack));
	return 0;
}
