#include "Slot.h"
#pragma once

#define MAX_TBL 100

typedef int HashFunc(Key k);

struct Table
{
	Slot tbl[MAX_TBL];
	HashFunc *hf;
};	

void TBLInit(Table *pt, HashFunc *f);

void TBLInsert(Table *pt, Key k, Value v);

Value TBLDelete(Table *pt, Key k);

Value TBLSearch(Table *pt, Key k);