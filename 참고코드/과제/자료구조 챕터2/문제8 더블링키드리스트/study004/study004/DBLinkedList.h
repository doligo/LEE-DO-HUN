#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int Data;

struct Node
{
	Data data;
	struct Node *next;
	struct Node *prev;
};

struct DBLinkedLists
{
	Node *head;
	Node *tail;
	Node *cur;
	int numofdata;
};

typedef DBLinkedLists List;

class DBLinkedList
{
public:

	void ListInit(List *plist);
	void LInsert(List *plist, Data data); // 꼬리에 노드를 추가한다.

	int LFirst(List *plist, Data *pdata);
	int LNext(List *plist, Data *pdata);
	int LPrevious(List *plist, Data *pdata);

	int LCount(List *plist);
	Data LRemove(List *plist); // 앞서 참조가 이뤄진 노드를 삭제

	// 머리,꼬리 부분 dummy로 바꿔서 추가하기 - 현재오류남
	// LRemove 구현하기

	DBLinkedList();
	~DBLinkedList();
};

