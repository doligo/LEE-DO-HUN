#include "Table.h"

Table::Table()
{

}

void Table::TBLInit(TableS *pt, HashFunc *f)
{
	int i;

	for (i = 0; i < MAX_TBL; i++)
		ListInit(&(pt->tbl[i]));

	pt->hf = f;
}

void Table::TBLInsert(TableS *pt, Key k, Value v)
{
	int hv = pt->hf(k);
	Slot ns = { k, v };

	LInsert(&(pt->tbl[hv]), ns);

	//if (TBLSearch(pt, k) != NULL)       // Ű�� �ߺ��Ǿ��ٸ�
	//{
		//printf("Ű �ߺ� ���� �߻� \n");
		//return;
	//	LInsert(&(pt->tbl[hv]), ns);
	//}
	//else
	//{
	//   LInsert(&(pt->tbl[hv]), ns);
	//}
}

Value Table::TBLDelete(TableS *pt, Key k)
{
	int hv = pt->hf(k);
	Slot cSlot;

	if (LFirst(&(pt->tbl[hv]), &cSlot))
	{
		if (cSlot.key == k)
		{
			LRemove(&(pt->tbl[hv]));
			return cSlot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &cSlot))
			{
				if (cSlot.key == k)
				{
					LRemove(&(pt->tbl[hv]));
					return cSlot.val;
				}
			}
		}
	}

	return NULL;
}

Value Table::TBLSearch(TableS *pt, Key k)
{
	int hv = pt->hf(k);
	Slot cSlot;

	if (LFirst(&(pt->tbl[hv]), &cSlot))
	{
		if (cSlot.key == k)
		{
			return cSlot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &cSlot))
			{
				if (cSlot.key == k)
					return cSlot.val;
			}
		}
	}

	return NULL;
}

Table::~Table()
{

}