#include "NameCard.h"
#include <iostream>
#pragma warning(disable:4996)

NameCard *MakeNameCard(char * name, char * phone)
{
	NameCard *cd = new NameCard;

	strcpy(cd->name, name);
	strcpy(cd->phone, phone);

	return cd;
}

void ShowNameCardInfo(NameCard *pcard)
{
	cout << "=====Á¤ º¸=====" << endl;
	cout << pcard->name << "   " << pcard->phone << endl;

	system("pause");
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