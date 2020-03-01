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
	NameCard *nc;
	nc = NULL;

	if (nc != NULL)
	{
		delete[] nc;
	}
	nc = new NameCard[PEOPLE_MAX];

	for (int i = 0; i < PEOPLE_MAX; i++)
	{
		MakeNameCard(nc[i].name, nc[i].phone);
	}

	Set(nc);

	ShowNameCardInfo(nc);

	system("pause");
}