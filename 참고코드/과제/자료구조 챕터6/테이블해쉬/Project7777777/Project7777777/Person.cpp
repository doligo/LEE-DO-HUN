#include "Person.h"

Person::Person()
{
}

int Person::GetSSN(PersonS *p)
{
	return p->ssn;
}

void Person::ShowPerInfo(PersonS *p)
{
	printf("�ֹε�Ϲ�ȣ: %d \n", p->ssn);
	printf("�̸�: %s \n", p->name);
	printf("�ּ�: %s \n\n", p->addr);
}

PersonS *Person::MakePersonData(int ssn, char *name, char *addr)
{
	PersonS *newP = new PersonS;

	newP->ssn = ssn;
	strcpy(newP->name, name);
	strcpy(newP->addr, addr);

	return newP;
}

Person::~Person()
{
}
