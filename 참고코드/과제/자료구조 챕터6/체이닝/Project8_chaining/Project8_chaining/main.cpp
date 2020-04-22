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

	cout << "Lee, Lin, KIM, HAN ���ԿϷ�" << endl;
	cout << endl;

	// ������ �Է� ///////
	np = PS.MakePersonData(900254, "Lee", "Seoul");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900254, "Lin", "Bunsan"); // ���� ���� Ű���� ������
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900139, "KIM", "Jeju");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);

	np = PS.MakePersonData(900827, "HAN", "Kangwon");
	TB.TBLInsert(&myTbl, PS.GetSSN(np), np);


	// ������ Ž�� ///////
	sp = TB.TBLSearch(&myTbl, 900254);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	sp = TB.TBLSearch(&myTbl, 900139);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	sp = TB.TBLSearch(&myTbl, 900827);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	// ������ ���� ///////
	rp = TB.TBLDelete(&myTbl, 900254);
	if (rp != NULL)
		free(rp);

	rp = TB.TBLDelete(&myTbl, 900139);
	if (rp != NULL)
		free(rp);

	rp = TB.TBLDelete(&myTbl, 900827);
	if (rp != NULL)
		free(rp);

	cout << "Lin, KIM, HAN ���� �Ϸ�" << endl;
	cout << endl;

	//////////////// �����Ŀ� ����Ű������ ����� ���� ������ ���

	sp = TB.TBLSearch(&myTbl, 900254);
	if (sp != NULL)
		PS.ShowPerInfo(sp);

	//// ü�̴��� ����Ű��(�ؽ�)�� �����ÿ� �ٸ������� ã���ʰ� ��Ű�帮��Ʈ�� �����ع�����

	return 0;
}