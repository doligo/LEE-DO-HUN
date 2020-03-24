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


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


void CLinkedList::StackInit(Clist *pstack) // ���� Last In First Out
{
	pstack->tail = NULL;
	pstack->cur = NULL;
	pstack->before = NULL;
	pstack->numofdata = 0;
}

int CLinkedList::SIsEmpty(Clist *pstack)
{
	if (pstack->tail == NULL || pstack->numofdata == NULL)
		return TRUE;
	else
		return FALSE;
}

void CLinkedList::SPush(Clist *pstack, Data data) // ���������Ϸ��� �Ӹ��κп� �߰�
{

	Node *newNode = new Node;

	newNode->data = data;

	if (pstack->tail == NULL)
	{
		pstack->tail = newNode;
		newNode->next = newNode;
	}

	else
	{
		newNode->next = pstack->tail->next;
		pstack->tail->next = newNode;
	}


	pstack->numofdata++;
}

Data CLinkedList::SPeek(Clist *pstack)
{
	if (SIsEmpty(pstack) == TRUE)
	{
		cout << "Stack Memory Error";
		exit(-1);
	}

	return pstack->tail->next->data;

}

Data CLinkedList::SPop(Clist *pstack)
{
	Data rdata;
	Node *rnode;

	if (SIsEmpty(pstack) == TRUE)
	{
		cout << "Stack Memory Error";
		exit(-1);
	}


	pstack->before = pstack->tail; // 1
	pstack->cur = pstack->tail->next; // 5

	rdata = pstack->cur->data;  // 5
	
	rnode = pstack->cur;

	pstack->before->next = pstack->cur->next; // 4
	pstack->cur = pstack->before; // 1

	free(rnode);
	pstack->numofdata--;


	return rdata;
}


CLinkedList::~CLinkedList()
{
}
