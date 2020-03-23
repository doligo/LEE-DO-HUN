#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
using namespace std;

typedef int Data;

struct Node
{
	Data data;
	struct Node *next;
};

struct Clist
{
	Node *tail;
	Node *cur;
	Node *before;
	int numofdata;
};

class CLinkedList
{
public:
	CLinkedList();

	void ListInit(Clist *plist);

	void LInsert(Clist *plist, Data data); // 꼬리로 추가한다

	int LFirst(Clist *plist, Data *pdata);
	int LNext(Clist *plist, Data *pdata);
	Data LRemove(Clist *plist);
	int LCount(Clist *plist);

	///////////////
	//// 스택으로 바꿔서 구현

	void StackInit(Clist *pstack);
	int SIsEmpty(Clist *pstack);

	~CLinkedList();
};

