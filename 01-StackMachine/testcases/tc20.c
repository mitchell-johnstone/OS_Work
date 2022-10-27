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

void doRotate(stackm *s, int d) 
{
	printf("Rotate Ret: %d\n", smRotate(s, d));
}

int main() {
	stackm mystack;
	smInit(&mystack);
	doPush(&mystack, 1);
	doPush(&mystack, 2);
	smPrint(&mystack);
	doRotate(&mystack, 2);
	smPrint(&mystack);
	doPop(&mystack);
	doPop(&mystack);
	return 0;
}
