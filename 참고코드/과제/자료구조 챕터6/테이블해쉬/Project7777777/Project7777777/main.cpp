#include "Table.h"

int GetHashValue(int n)
{
	return n % 100;
}

int main()
{
	Table TB;
	Person PS;

	PersonS pss;
	TableS tbs;

	TB.TBLInit(&tbs, GetHashValue); // 초기화

	TB.TBLInsert(&tbs, );

	system("pause");
}