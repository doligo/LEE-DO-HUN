#include "Slot.h"
#pragma once

#define TRUE 1
#define FALSE 0

//typedef int LData;
typedef Slot LData;

struct Node
{
	LData data; // Slot ÇüÀÌ´Ù
	struct Node *next;
};

struct LinkedList
{
	Node *head;
	Node *cur;
	Node *before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
};

typedef LinkedList List;

class DLinkedList
{
public:

	void ListInit(List *plist);
	void LInsert(List *plist, LData data);

	int LFirst(List *plist, LData *pdata);
	int LNext(List *plist, LData *pdata);

	LData LRemove(List *plist);
	int LCount(List *plist);

	void SetSortRule(List *plist, int(*comp)(LData d1, LData d2));

	DLinkedList();
	~DLinkedList();
};

