#include "CLinkedList.h"



CLinkedList::CLinkedList()
{
}

void CLinkedList::ListInit(Clist *plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numofdata = 0;
}

void CLinkedList::LInsert(Clist *plist, Data data)
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
		plist->tail = newNode;
	}

	plist->numofdata++;
}

int CLinkedList::LFirst(Clist *plist, Data *pdata)
{
	if (plist->tail == NULL)    // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int CLinkedList::LNext(Clist *plist, Data *pdata)
{
	if (plist->tail == NULL)    // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

Data CLinkedList::LRemove(Clist *plist)
{
	Node *rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail)    // 삭제 대상을 tail이 가리킨다면
	{
		if (plist->tail == plist->tail->next)    // 그리고 마지막 남은 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	plist->numofdata--;
	return rdata;
}

int CLinkedList::LCount(Clist *plist)
{
	return plist->numofdata;
}

////////////////////////////

void CLinkedList::StackInit(Clist *pstack)
{
	pstack->tail = NULL;
	pstack->numofdata = 0;
}

int CLinkedList::SIsEmpty(Clist *pstack)
{
	if (pstack->tail == NULL)
		return TRUE;
	else
		return FALSE;
}

CLinkedList::~CLinkedList()
{
}
