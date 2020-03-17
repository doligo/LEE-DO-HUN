#pragma once
#include <stdio.h>
#include <stdlib.h>

#define TURE 1
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
	void ListInit(Clist *plist);

	void LInsert(Clist *plist, Data data);
	void LInderFront(Clist *plist, Data data); // 두개 합칠시 enum을 추가해주면 유용

	int LFirst(Clist *plist, Data *pdata);
	int LNext(Clist *plist, Data *pdata);
	Data LRemove(Clist *plist);
	int LCount(Clist *plist);

	CLinkedList();
	~CLinkedList();
};

