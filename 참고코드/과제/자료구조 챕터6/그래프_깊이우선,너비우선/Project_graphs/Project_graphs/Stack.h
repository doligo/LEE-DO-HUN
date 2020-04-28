#include <stdio.h>
#include <stdlib.h>
#pragma once

#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef int Data;

struct ArrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
};

typedef ArrayStack Stacks;

class Stack
{
public:
	void StackInit(Stacks *pstack);
	int SIsEmpty(Stacks *pstack);

	void SPush(Stacks *pstack, Data data);
	Data SPop(Stacks *pstack);
	Data SPeek(Stacks *pstack);
	Stack();
	~Stack();
};

