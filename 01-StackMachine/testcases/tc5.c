#include <stdio.h>
#include "stackm.c"

int main() {
	stackm mystack;
	smInit(&mystack);
	printf("SIZE: %d\n", smSize(&mystack));
	return 0;
}
