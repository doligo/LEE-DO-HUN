#pragma once
#include"Mecro.h"

#define MAX_WEAPON 30

struct Weapon_Info
{
	string weapon_type;
	string weapon_name;
	int weapon_dmg;
	int weapon_price;
	int weapon_max_count;
};

class Weapon
{
public:
	void Init(Weapon_Info *name);
	Weapon();
	~Weapon();
};

