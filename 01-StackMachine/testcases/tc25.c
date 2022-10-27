#include <stdio.h>
#include "stackm.c"

int main() {
	stackm mystack;
	smInit(&mystack);
	for(int i = 0 ; i < 1000; i++) {
		smPush(&mystack, i);
	}
	smPrint(&mystack);
	for(int i = 0 ; i < 1000; i++) {
		smPop(&mystack);
	}
	smPrint(&mystack);
	return 0;
}
