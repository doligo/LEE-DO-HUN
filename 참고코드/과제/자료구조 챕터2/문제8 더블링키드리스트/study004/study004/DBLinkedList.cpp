#include "DBLinkedList.h"


DBLinkedList::DBLinkedList()
{
}

void DBLinkedList::ListInit(List *plist)
{
	plist->head = new Node; // dummy
	plist->tail = new Node; // dummy

	plist->head->next = NULL;
	plist->head->prev = NULL;
	plist->tail->next = NULL;
	plist->tail->prev = NULL;

	plist->numofdata = 0;
}

void DBLinkedList::LInsert(List *plist, Data data)
{
	Node *newNode = new Node;

	newNode->data = data;
	newNode->next = plist->head->next;

	if (plist->numofdata == NULL)
	{
		newNode->prev = NULL;
		plist->tail->next = newNode;
		plist->head->next = plist->tail->next;
		plist->numofdata++;
	}

	else // 두번째 추가부터
	{
		plist->head->next->prev = newNode;
		plist->head->next = newNode;
		plist->numofdata++;
	}
}

int DBLinkedList::LFirst(List *plist, Data *pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->cur = plist->head->next;
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
	if (plist->cur->prev == plist->head->next->prev)
	{
		return FALSE;
	}

	plist->cur = plist->cur->prev;

	*pdata = plist->cur->data;

	return TRUE;

}

Data DBLinkedList::LRemove(List *plist)
{
	Node *tmp = plist->cur; // ex) 30이면
	int tmpdata = plist->cur->data;

	plist->cur->next->prev = plist->cur->prev;
	plist->cur->prev->next = plist->cur->next;
	plist->cur = plist->cur->next;

	free(tmp);

	return tmpdata;
}

int DBLinkedList::LCount(List *plist)
{
	return plist->numofdata;
}

DBLinkedList::~DBLinkedList()
{
}
