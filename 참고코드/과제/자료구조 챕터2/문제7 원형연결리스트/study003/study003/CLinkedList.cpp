#include "CLinkedList.h"



CLinkedList::CLinkedList()
{
}

void ListInit(Clist *plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numofdata = 0;
}

void LInsertFront(Clist *plist, Data data)
{
	Node *newNode = new Node;
	newNode->data = data;

	if (plist->tail == NULL)
	{
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
	}
}

CLinkedList::~CLinkedList()
{
}
