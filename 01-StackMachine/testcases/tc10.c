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

int main() {
	stackm mystack;
	smInit(&mystack);
	doPush(&mystack, 1);
	smPrint(&mystack);
	doPush(&mystack, 2);
	smPrint(&mystack);
	doPush(&mystack, 3);
	smPrint(&mystack);
	doPop(&mystack);
	smPrint(&mystack);
	doPop(&mystack);
	smPrint(&mystack);
	doPop(&mystack);
	smPrint(&mystack);
	return 0;
}
