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

struct Deques
{
	Node *head;
	Node *tail;
};

class Deque
{
public:
	Deque();
	void DequeInit(Deques * pdeq);
	int DQIsEmpty(Deques * pdeq);

	void DQAddFirst(Deques * pdeq, Data data);
	void DQAddLast(Deques * pdeq, Data data);

	Data DQRemoveFirst(Deques * pdeq);
	Data DQRemoveLast(Deques * pdeq);

	Data DQGetFirst(Deques * pdeq);
	Data DQGetLast(Deques * pdeq);
	~Deque();
};

