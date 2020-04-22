#include "Person.h"

Person::Person()
{

}

int Person::GetSSN(PersonS *p)
{
	return p->ssn;
}

void Person::ShowPerInfo(PersonS * p)
{
	printf("�ֹε�Ϲ�ȣ: %d \n", p->ssn);
	printf("�̸�: %s \n", p->name);
	printf("�ּ�: %s \n\n", p->addr);
}

PersonS *Person::MakePersonData(int ssn, const char * name, const char * addr)
{
	PersonS * newP = (PersonS*)malloc(sizeof(PersonS));

	newP->ssn = ssn;
	strcpy_s(newP->name, name);
	strcpy_s(newP->addr, addr);
	return newP;
}

Person::~Person()
{

}