#include "Table.h"

int GetHashValue(int hf)
{
	return hf % 100;
}

int main()
{
	Table TB;
	TableS tbs;

	TB.TBLInit(&tbs, GetHashValue());

	system("pause");
}