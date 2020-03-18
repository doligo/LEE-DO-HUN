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

void CLinkedList::LInsert(Clist *plist, Data data, int pos)
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
		if (pos == POSITION_FRONT) // 0
		{
			newNode->next = plist->tail->next;
			plist->tail->next = newNode;
		}
		else // POSITION_NEXT 1
		{
			newNode->next = plist->tail->next;
			plist->tail->next = newNode;
			plist->tail = newNode;
		}
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

int CLinkedList::Find_Person(Clist *plist, int person_num, int num)
{
	if (plist->tail == NULL)    // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->tail; // 처음노드에서 먼저 찾는다
	plist->cur = plist->tail->next;
	if (plist->cur->data == person_num) // 찾았으면 리턴
	{
		for (int j = 0; j < num; j++)
		{
			plist->before = plist->cur;
			plist->cur = plist->cur->next;
		}
		return plist->cur->data;
	}

	for (int i = 0; i < PEOPLE_MAX - 1; i++) // 첫번째 노드빼고 나머지 찾는다
	{
		plist->before = plist->cur;
		plist->cur = plist->cur->next;

		if (plist->cur->data == person_num) // 찾으면 리턴
		{
			for (int j = 0; j < num; j++)
			{
				plist->before = plist->cur;
				plist->cur = plist->cur->next;
			}
			return plist->cur->data;
		}
	}
}

CLinkedList::~CLinkedList()
{
}
