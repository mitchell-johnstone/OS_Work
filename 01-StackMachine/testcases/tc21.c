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
	for(int i = 0 ; i < 10; i++) {
		doPush(&mystack, i);
	}
	smPrint(&mystack);
	for(int i = 0; i < 10; i++) {
		doRotate(&mystack, i+1);
		smPrint(&mystack);
	}
	for(int i = 0; i < 10; i++) {
		doPop(&mystack);
	}
	return 0;
}
