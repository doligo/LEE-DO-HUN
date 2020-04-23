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
	printf("등록번호: %d \n", p->ssn);
	printf("무기이름: %s \n", p->name);
	printf("데미지: %d \n\n", p->dam);
	printf("무기가격: %d \n\n", p->price);
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