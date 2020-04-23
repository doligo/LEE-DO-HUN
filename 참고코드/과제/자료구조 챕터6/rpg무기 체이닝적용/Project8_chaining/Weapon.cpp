#include "Weapon.h"

Weapon::Weapon()
{

}

int Weapon::GetSSN(WeaponS *p)
{
	return p->ssn;
}

void Weapon::ShowWeaponInfo(WeaponS *p)
{
	printf("��Ϲ�ȣ: %d \n", p->ssn);
	printf("�����̸�: %s \n", p->name);
	printf("������: %d \n\n", p->dam);
	printf("���Ⱑ��: %d \n\n", p->price);
}

WeaponS *Weapon::MakeWeaponData(int ssn, const char * name, int dam, int price)
{
	WeaponS * newW = (WeaponS*)malloc(sizeof(WeaponS));

	newW->ssn = ssn;
	strcpy_s(newW->name, name);
	newW->dam = dam;
	newW->price = price;
	return newW;
}

Weapon::~Weapon()
{

}