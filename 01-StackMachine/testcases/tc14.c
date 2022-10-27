#include <stdio.h>
#include "stackm.c"

void doPush(stackm* s, int v)
{
	printf("Push Ret: %d\n", smPush(s, v));
}

void doSub(stackm* s) 
{
	printf("Sub Ret: %d\n", smSub(s));
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
	for(int i = 0 ; i < 10; i++) {
		doPush(&mystack, i);
	}
	for(int i = 0; i < 9; i++) {
		doSub(&mystack);
	}
	doTop(&mystack, &val);
	printf("Final Val: %d\n", val);
	doPop(&mystack);
	
	return 0;
}
