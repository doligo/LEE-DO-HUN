#include "Table.h"

int GetHashValue(int n)
{
	return n % 100;
}

int main()
{
	Table TB;
	Person PS;

	TableS *tbs = new TableS;
	PersonS *pss = new PersonS;

	char tt[10] = "Simon";
	char tt2[10] = "Korea";
	char dd[10] = "Mina";
	char dd2[10] = "Japan";

	int tmp_key[10] = {};
	int i = 0;

	TB.TBLInit(tbs, GetHashValue); // 초기화

	pss = PS.MakePersonData(12300, tt, tt2);
	
	TB.TBLInsert(tbs, 111, pss);
	tmp_key[i] = 111, i++;

	pss = PS.MakePersonData(15300, dd, dd2);
	TB.TBLInsert(tbs, 155, pss);
	tmp_key[i] = 155, i++;

	for (int j = 0; j < i; j++)
	{
		pss = TB.TBLSearch(tbs, tmp_key[j]);
		PS.ShowPerInfo(pss);
	}

	///// 삭제 

	pss = TB.TBLDelete(tbs, tmp_key[0]);
	free(pss);
	pss = TB.TBLSearch(tbs, tmp_key[0]);
	if (pss == NULL)
		cout << "삭제된 데이터입니다" << endl;

	system("pause");
}