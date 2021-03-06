#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List * plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
	plist->comp = NULL;
}

int LFirst(List * plist, LData * pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List * plist)
{
	Node * rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next; // before의 꼬랑지부분에 cur->next의 전체값을 붙임
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}

void Insert(List * plist, LData data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	Node *tmp = (Node*)malloc(sizeof(Node));
	Node *tmp2 = (Node*)malloc(sizeof(Node));

	newNode->data = data; // x,y 값 저장
	tmp = plist->head->next; // 주소값전달
	tmp2 = plist->head; // 똑같이 주소값전달

	if (plist->numOfData == NULL) // 처음
	{
		newNode->next = plist->head->next;
		plist->head->next = newNode;
		(plist->numOfData)++;
	}
	
	else
	{
		while (plist->comp(tmp, newNode) == 1)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		newNode->next = tmp; // null 대입
		tmp2->next = newNode; // tmp2에 대입된것이 plist->head도 똑같이 대입된다
		(plist->numOfData)++;
	}

}

void SetSortRule(List * plist, int(*comp)(Node *d1, Node *d2))
{
	plist->comp = comp;
}