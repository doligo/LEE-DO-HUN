#include "Table.h"

int MyHashFunc(int n)
{
	return n % 100;
}

int main(void)
{
	Table TB;
	Person PS;

	TableS myTbl;
	PersonS *np;
	PersonS *sp;
	PersonS *rp;

	TB.TBLInit(&myTbl, MyHashFunc);

	cout << "Lee, Lin, KIM, HAN 삽입완료" << endl;
	cout << endl;

	// 데이터 입력 ///////
	np = PS.MakePersonData(900254, "Lee", "Seoul");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900254, "Lin", "Bunsan"); // 위와 같은 키값을 가졌다
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900139, "KIM", "Jeju");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900827, "HAN", "Kangwon");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);


	// 데이터 탐색 ///////
	sp = TB.TBLSearch(&myTbl, 900254);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	sp = TB.TBLSearch(&myTbl, 900139);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	sp = TB.TBLSearch(&myTbl, 900827);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	// 데이터 삭제 ///////
	rp = TB.TBLDelete(&myTbl, 900254);
	if (rp != NULL)
		free(rp);

	rp = TB.TBLDelete(&myTbl, 900139);
	if (rp != NULL)
		free(rp);

	rp = TB.TBLDelete(&myTbl, 900827);
	if (rp != NULL)
		free(rp);

	cout << "Lin, KIM, HAN 삭제 완료" << endl;
	cout << endl;

	//////////////// 삭제후에 값은키값으로 저장된 다음 데이터 출력

	sp = TB.TBLSearch(&myTbl, 900254);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	//// 체이닝은 값은키값(해시)을 가질시에 다른공간을 찾지않고 링키드리스트로 저장해버린다

	return 0;
}