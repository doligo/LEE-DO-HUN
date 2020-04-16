#include "Table.h"


Table::Table()
{
}

void Table::TBLInit(TableS *pt, HashFunc *f)
{
	for (int i = 0; i < MAX_TBL; i++)
	{
		(pt->tbl[i]).status = EMPTY;
	}

	pt->hf = f;
}

void Table::TBLInsert(TableS *pt, Key k, Value v)
{
	int hv = pt->hf(k);
	pt->tbl[hv].val = v;
	pt->tbl[hv].key = k;
	pt->tbl[hv].status = INUSE;
}

Value Table::TBLDelete(TableS *pt, Key k)
{
	int hv = pt->hf(k);

	if ((pt->tbl[hv]).status != INUSE)
	{
		return NULL;
	}
	else
	{
		(pt->tbl[hv]).status = DELETED;
		return (pt->tbl[hv]).val;
	}
}

Value Table::TBLSearch(TableS *pt, Key k)
{
	int hv = pt->hf(k);

	if ((pt->tbl[hv]).status != INUSE)
		return NULL;
	else
		return (pt->tbl[hv]).val;
}

Table::~Table()
{
}
