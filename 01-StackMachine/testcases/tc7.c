#include <stdio.h>
#include "stackm.c"

void doPush(stackm* s, int v)
{
	printf("Push Ret: %d\n", smPush(s, v));
}

void doPop(stackm* s) 
{
	printf("Pop Ret: %d\n", smPop(s));
}

void doTop(stackm* s, int* v)
{
	printf("Top Ret: %d\n", smTop(s, v));
}

int main() {
	int val = 0;
	stackm mystack;
	smInit(&mystack);
	doPush(&mystack, 1);
	doTop(&mystack, &val);
	printf("TOP: %d\n", val);
	doPush(&mystack, 2);
	doTop(&mystack, &val);
	printf("TOP: %d\n", val);
	doPush(&mystack, 3);
	doTop(&mystack, &val);
	printf("TOP: %d\n", val);
	doPop(&mystack);
	doPop(&mystack);
	doPop(&mystack);
	return 0;
}
