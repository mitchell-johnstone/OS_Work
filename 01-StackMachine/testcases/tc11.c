#include <stdio.h>
#include "stackm.c"

void doPush(stackm* s, int v)
{
	printf("Push Ret: %d\n", smPush(s, v));
}

void doAdd(stackm* s) 
{
	printf("Add Ret: %d\n", smAdd(s));
}

void doPop(stackm* s) 
{
	printf("Pop Ret: %d\n", smPop(s));
}

int main() {
	stackm mystack;
	smInit(&mystack);
	doPush(&mystack, 1);
	doPush(&mystack, 2);
	doAdd(&mystack);
	doPop(&mystack);
	return 0;
}
