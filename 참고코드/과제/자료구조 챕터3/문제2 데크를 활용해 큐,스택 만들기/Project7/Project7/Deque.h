#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int Data;

struct Node
{
	Data data;
	struct Node *next;
	struct Node *prev;
};

struct Head_Tail
{
	Node *head;
	Node *tail;
};

class Deque
{
public:
	Deque();
	void DequeInit(Head_Tail * pdeq);
	int DQIsEmpty(Head_Tail * pdeq);

	void DQAddFirst(Head_Tail * pdeq, Data data);
	void DQAddLast(Head_Tail * pdeq, Data data);

	Data DQRemoveFirst(Head_Tail * pdeq);
	Data DQRemoveLast(Head_Tail * pdeq);

	Data DQGetFirst(Head_Tail * pdeq);
	Data DQGetLast(Head_Tail * pdeq);
	~Deque();
};

