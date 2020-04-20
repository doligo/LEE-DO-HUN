#include "User.h"

int GetSSN(User_Info *p)
{
	return p->phone_num;
}

void ShowPerInfo(User_Info *p)
{
	printf("주민등록번호: %d \n", p->phone_num);
	printf("이름: %s \n", p->name);
	printf("주소: %s \n\n", p->addr);
}

User_Info *MakePersonData(int ssn, char *name, char *addr)
{
	User_Info *newU = new User_Info;

	newU->phone_num = ssn;
	strcpy(newU->name, name);
	strcpy(newU->addr, addr);

	return newU;
}