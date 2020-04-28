#include "Stack.h"



Stack::Stack()
{
}

void Stack::StackInit(Stacks * pstack)
{
	pstack->topIndex = -1;
}

int Stack::SIsEmpty(Stacks * pstack)
{
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void Stack::SPush(Stacks * pstack, Data data)
{
	pstack->topIndex += 1;
	pstack->stackArr[pstack->topIndex] = data;
}

Data Stack::SPop(Stacks * pstack)
{
	int rIdx;

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rIdx = pstack->topIndex;
	pstack->topIndex -= 1;

	return pstack->stackArr[rIdx];
}

Data Stack::SPeek(Stacks * pstack)
{
	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];
}

Stack::~Stack()
{
}
