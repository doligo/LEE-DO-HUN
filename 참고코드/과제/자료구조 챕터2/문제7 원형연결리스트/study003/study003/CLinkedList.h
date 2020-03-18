#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define PEOPLE_MAX 4

using namespace std;

typedef int Data;

enum POSITION
{
	POSITION_FRONT = 0,
	POSITION_NEXT = 1
};

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

struct Employee // 사원
{
	string name; // 사원이름
	Data num; // 사원번호
};

class CLinkedList
{
public:
	CLinkedList();

	void ListInit(Clist *plist);

	void LInsert(Clist *plist, Data data, int pos);

	int LFirst(Clist *plist, Data *pdata);
	int LNext(Clist *plist, Data *pdata);
	Data LRemove(Clist *plist);
	int LCount(Clist *plist);
	int Find_Person(Clist *plist, int person_num, int num);

	~CLinkedList();
};

