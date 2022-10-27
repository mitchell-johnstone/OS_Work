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

int main() {
	stackm mystack;
	smInit(&mystack);
	doAdd(&mystack);
	doPush(&mystack, 10);
	doAdd(&mystack);
	return 0;
}
