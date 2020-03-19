#include "DBLinkedList.h"


DBLinkedList::DBLinkedList()
{
}

void DBLinkedList::ListInit(List *plist)
{
	plist->head = NULL;
	plist->tail = NULL;
	plist->numofdata = 0;
}

void DBLinkedList::LInsert(List *plist, Data data)
{
	Node *newNode = new Node;
	newNode->data = data;

	newNode->next = plist->tail; // NULL로 초기화

	if (plist->head != NULL)
		plist->head->prev = newNode;

	newNode->prev = NULL;
	plist->head = newNode;

	plist->numofdata++;
}

int DBLinkedList::LFirst(List *plist, Data *pdata)
{
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;
	*pdata = plist->cur->data;
	return TRUE;
}

int DBLinkedList::LNext(List *plist, Data *pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}

int DBLinkedList::LPrevious(List *plist, Data *pdata)
{
	if (plist->cur->prev == NULL)
	{
		return FALSE;
	}
	
	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;
	return TRUE;
}

int DBLinkedList::LCount(List *plist)
{
	return plist->numofdata;
}

DBLinkedList::~DBLinkedList()
{
}
