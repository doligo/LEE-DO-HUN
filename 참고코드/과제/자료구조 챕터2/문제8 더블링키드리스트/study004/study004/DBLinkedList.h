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
	void LInsert(List *plist, Data data); // ������ ��带 �߰��Ѵ�.

	int LFirst(List *plist, Data *pdata);
	int LNext(List *plist, Data *pdata);
	int LPrevious(List *plist, Data *pdata);

	int LCount(List *plist);
	Data LRemove(List *plist); // �ռ� ������ �̷��� ��带 ����

	// �Ӹ�,���� �κ� dummy�� �ٲ㼭 �߰��ϱ� - ���������
	// LRemove �����ϱ�

	DBLinkedList();
	~DBLinkedList();
};

