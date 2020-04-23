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
	printf("무기타입: %s \n", p->type);
	printf("무기이름: %s \n", p->name);
	printf("데미지: %d \n", p->dam);
	printf("무기가격: %d \n\n", p->price);
}

WeaponS *Weapon::MakeWeaponData(const char * type, const char * name, int dam, int price, int hsn)
{
	WeaponS * newW = (WeaponS*)malloc(sizeof(WeaponS));

	strcpy_s(newW->type, type);
	strcpy_s(newW->name, name);
	newW->dam = dam;
	newW->price = price;
	newW->hsn = hsn; // 키(해시값)
	return newW;
}

Weapon::~Weapon()
{

}