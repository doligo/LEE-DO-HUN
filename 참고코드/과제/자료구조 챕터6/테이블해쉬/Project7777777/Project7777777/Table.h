#include "Slot.h"
#pragma once

#define MAX_TBL 100

typedef int HashFunc(Key k);

typedef struct TableS
{
	Slot tbl[MAX_TBL];
	HashFunc *hf;
};

class Table
{
public:
	Table();

	void TBLInit(TableS *pt, HashFunc *f);

	void TBLInsert(TableS *pt, Key k, Value v);

	Value TBLDelete(TableS *pt, Key k);

	Value TBLSearch(TableS *pt, Key k);

	~Table();
};

