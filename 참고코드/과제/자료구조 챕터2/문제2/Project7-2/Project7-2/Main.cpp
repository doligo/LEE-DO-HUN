#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

void Set(NameCard *n)
{
	strcpy(n[0].name, "test1");
	strcpy(n[0].phone, "01011");

	strcpy(n[1].name, "test2");
	strcpy(n[1].phone, "01022");

	strcpy(n[2].name, "test3");
	strcpy(n[2].phone, "01033");
}

void main()
{
	int select = 0;
	NameCard *nc;
	nc = NULL;

	if (nc != NULL)
	{
		delete[] nc;
	}
	nc = new NameCard[PEOPLE_MAX];

	
	MakeNameCard(nc->name, nc->phone);

	Set(nc);

	cout << "1.정보보기" << endl;
	cout << "2.번호변경" << endl;
	cout << "3.정보삭제" << endl;
	cout << "입력 : ";
	cin >> select;

	switch (select)
	{
	case 1:
		ShowNameCardInfo(nc);
		break;
	case 2:
		break;
	case3:
		break;
	}


	system("pause");
}