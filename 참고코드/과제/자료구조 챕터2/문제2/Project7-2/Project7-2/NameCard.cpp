#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

NameCard *MakeNameCard(char * name, char * phone) // 이거 복습
{
	NameCard *cd = new NameCard; // 구조체 동적할당 후 return 으로 할당한 주소값 main에 전달

	strcpy(cd->name, name);
	strcpy(cd->phone, phone);

	return cd;
}

void ShowNameCardInfo(NameCard *pcard)
{
	cout << "=====정 보=====" << endl;
	cout << pcard->name << "   " << pcard->phone << endl;

}

void ChangePhoneNum(NameCard * pcard, char * phone)
{
	strcpy(pcard->phone, phone);
}

int NameCompare(NameCard * pcard, char * name)
{
	string tmp1;
	string tmp2;

	tmp1 = pcard->name;
	tmp2 = name;
	if (tmp1 == tmp2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Delete(NameCard *pcard)
{
	delete pcard;
}