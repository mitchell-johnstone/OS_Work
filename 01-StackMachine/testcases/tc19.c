#include <stdio.h>
#include "stackm.c"

void doPush(stackm* s, int v)
{
	printf("Push Ret: %d\n", smPush(s, v));
}

void doMult(stackm* s) 
{
	printf("Mult Ret: %d\n", smMult(s));
}

void doPop(stackm* s) 
{
	printf("Pop Ret: %d\n", smPop(s));
}

int main() {
	stackm mystack;
	smInit(&mystack);
	doMult(&mystack);
	doPush(&mystack, 10);
	doMult(&mystack);
	return 0;
}
