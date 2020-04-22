#include "Slot.h"
#include "DLinkedList.h"
#pragma once

#define MAX_TBL 100

typedef int HashFunc(Key k);

struct TableS
{
	List tbl[MAX_TBL];
	HashFunc *hf;
};

class Table : virtual public DLinkedList
{
public:

	void TBLInit(TableS *pt, HashFunc *f);
	void TBLInsert(TableS *pt, Key k, Value v);
	Value TBLDelete(TableS *pt, Key k);
	Value TBLSearch(TableS *pt, Key k);

	Table();
	~Table();
};

