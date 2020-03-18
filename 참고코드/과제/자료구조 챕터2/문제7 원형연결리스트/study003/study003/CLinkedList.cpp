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
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int CLinkedList::LNext(Clist *plist, Data *pdata)
{
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
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

	if (rpos == plist->tail)    // ���� ����� tail�� ����Ų�ٸ�
	{
		if (plist->tail == plist->tail->next)    // �׸��� ������ ���� �����
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
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->tail; // ó����忡�� ���� ã�´�
	plist->cur = plist->tail->next;
	if (plist->cur->data == person_num) // ã������ ����
	{
		for (int j = 0; j < num; j++)
		{
			plist->before = plist->cur;
			plist->cur = plist->cur->next;
		}
		return plist->cur->data;
	}

	for (int i = 0; i < PEOPLE_MAX - 1; i++) // ù��° ��廩�� ������ ã�´�
	{
		plist->before = plist->cur;
		plist->cur = plist->cur->next;

		if (plist->cur->data == person_num) // ã���� ����
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
