#include "stackm.h"
#include <stdio.h>
#include <stdlib.h>

void smInit(struct stackm *myStack)
{
	myStack->top = NULL;	
}

int smSize(struct stackm *myStack)
{
	struct node *cur = myStack->top;
	int cnt = 0;
	while(cur != NULL){
		cur = cur->next;
		cnt++;
	}
	return cnt;
}

int smPush(struct stackm *myStack, int toStore)
{
	struct node *newTop = malloc(sizeof(struct node));
	if(newTop == NULL) return 0;
	newTop->value = toStore;
	newTop->next = myStack->top;
	myStack->top = newTop;
	return 1;
}

int smPop(struct stackm *myStack)
{
	if(myStack->top == NULL) return 0;
	struct node *oldTop = myStack->top;
	myStack->top = oldTop->next;
	free(oldTop);
	return 1;
}

int smTop(struct stackm *myStack, int* toStore)
{
	if(toStore == NULL) return 0;
	if(myStack->top == NULL) return 0;
	*toStore = myStack->top->value;
	return 1;
}

void smClear(struct stackm *myStack)
{
	while(myStack->top != NULL) smPop(myStack);
}

void smPrint(struct stackm *myStack)
{
	printf("Current Stack Contents:\n");
	if(myStack->top == NULL) {
		printf("Empty\n");
	} else {
		printf("top:%i\n", myStack->top->value);
		struct node *cur = myStack->top->next;
		while(cur!= NULL){
			printf("    %i\n", cur->value);
			cur = cur->next;
		}
	}
}

int smAdd(struct stackm* myStack)
{
	if(smSize(myStack) < 2) return 0;
	int topValue;
	smTop(myStack, &topValue);
	smPop(myStack);
	myStack->top->value += topValue;
	return 1;
}

int smSub(struct stackm* myStack)
{
	if(smSize(myStack) < 2) return 0;
	int topValue;
	smTop(myStack, &topValue);
	smPop(myStack);
	myStack->top->value -= topValue;
	myStack->top->value *= -1;
	return 1;
}

int smMult(struct stackm* myStack)
{
	if(smSize(myStack) < 2) return 0;
	int topValue;
	smTop(myStack, &topValue);
	smPop(myStack);
	myStack->top->value *= topValue;
	return 1;
}

int smRotate(struct stackm* myStack, int depth)
{
	if(depth <= 0) return 0;
	if(smSize(myStack) < depth) return 0;
	if(depth != 1){
		struct node *oldTop = myStack->top;
		struct node *curTop = oldTop->next;
		myStack->top = curTop;
		for(int i = 0; i < depth-2; i++){
			curTop = curTop->next;
		}
		oldTop->next = curTop->next;
		curTop->next = oldTop;
	}
	return 1;
}

