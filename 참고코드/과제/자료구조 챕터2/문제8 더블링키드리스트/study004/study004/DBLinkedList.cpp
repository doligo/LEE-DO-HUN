#include "DBLinkedList.h"


DBLinkedList::DBLinkedList()
{
}

void DBLinkedList::ListInit(List *plist)
{
	plist->head = NULL;
	plist->head->next = NULL;
	plist->tail = NULL;
	plist->tail->next = NULL;
	plist->cur = NULL;
	plist->numofdata = 0;
}

void DBLinkedList::LInsert(List *plist, Data data)
{
	Node *newNode = new Node;

	newNode->data = data;
	newNode->next = plist->tail->next;

	if (plist->tail->next != NULL)
		plist->tail->prev = newNode;

	newNode->prev = NULL;
	plist->tail->next = newNode;

	plist->numofdata++;
}

int DBLinkedList::LFirst(List *plist, Data *pdata)
{
	if (plist->tail->next == NULL)
		return FALSE;

	plist->cur = plist->tail->next;
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
