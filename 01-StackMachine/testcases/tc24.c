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

void doRotate(stackm *s, int d) 
{
	printf("Rotate Ret: %d\n", smRotate(s, d));
}

void doTop(stackm* s, int* v)
{
	printf("Top Ret: %d\n", smTop(s, v));
}

int main() {
	int val = 0;
	stackm mystack;
	smInit(&mystack);
	for(int i = 1 ; i <= 10; i++) {
		doPush(&mystack, i);
		doPush(&mystack, i);
		doMult(&mystack);
	}
	smPrint(&mystack);
	doTop(&mystack, &val);
	while(val > 25) {
		doRotate(&mystack, 10);
		doTop(&mystack, &val);
	}
	smPrint(&mystack);
	smClear(&mystack);
	return 0;
}
