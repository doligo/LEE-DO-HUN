#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#pragma once
using namespace std;

#define STR_LEN 50

struct WeaponS
{
	char type[STR_LEN];
	char name[STR_LEN];
	int dam;
	int price;
	int hsn;
};

class Weapon
{
private:
public:
	Weapon();

	int GetSSN(WeaponS *p);
	void ShowWeaponInfo(WeaponS *p);
	WeaponS *MakeWeaponData(const char * type, const char * name, int dam, int price, int hsn);

	~Weapon();
};

