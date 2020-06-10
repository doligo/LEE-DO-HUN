#include "Weapon.h"



Weapon::Weapon()
{
}

void Weapon::Init(Weapon_Info *name)
{
	if (name != NULL)
	{
		delete[] name;
	}
}

Weapon::~Weapon()
{
}
