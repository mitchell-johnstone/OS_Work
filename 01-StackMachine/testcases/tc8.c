#include <stdio.h>
#include "stackm.c"

int main() {
	stackm mystack;
	smInit(&mystack);
	smClear(&mystack);
	return 0;
}
