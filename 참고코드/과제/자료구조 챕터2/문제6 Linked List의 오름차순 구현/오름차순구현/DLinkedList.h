#include "Point.h"
#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE	1
#define FALSE	0

typedef Point * LData;

struct Node // 포인터로 구현
{
	LData data;
	struct Node *next;
};

typedef struct _linkedList
{
	Node * head;
	Node * cur;
	Node * before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
} LinkedList;


typedef LinkedList List;

void ListInit(List * plist);

int LFirst(List * plist, LData * pdata);
int LNext(List * plist, LData * pdata);

LData LRemove(List * plist);
int LCount(List * plist);


void Insert(List * plist, LData data);
void SetSortRule(List * plist, int(*comp)(LData d1, LData d2));

#endif