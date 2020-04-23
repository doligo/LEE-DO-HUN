#include "Weapon.h"

Weapon::Weapon()
{

}

int Weapon::GetSSN(WeaponS *p)
{
	return p->hsn;
}

void Weapon::ShowWeaponInfo(WeaponS *p)
{
	printf("����Ÿ��: %s \n", p->type);
	printf("�����̸�: %s \n", p->name);
	printf("������: %d \n", p->dam);
	printf("���Ⱑ��: %d \n\n", p->price);
}

WeaponS *Weapon::MakeWeaponData(const char * type, const char * name, int dam, int price, int hsn)
{
	WeaponS * newW = (WeaponS*)malloc(sizeof(WeaponS));

	strcpy_s(newW->type, type);
	strcpy_s(newW->name, name);
	newW->dam = dam;
	newW->price = price;
	newW->hsn = hsn; // Ű(�ؽð�)
	return newW;
}

Weapon::~Weapon()
{

}