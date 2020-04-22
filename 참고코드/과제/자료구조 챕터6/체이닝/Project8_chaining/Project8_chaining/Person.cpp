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
	printf("주민등록번호: %d \n", p->ssn);
	printf("이름: %s \n", p->name);
	printf("주소: %s \n\n", p->addr);
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