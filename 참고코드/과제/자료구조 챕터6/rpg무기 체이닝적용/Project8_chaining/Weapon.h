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
	int ssn;
	char name[STR_LEN];
	int dam;
	int price;
};

class Weapon
{
private:
public:
	Weapon();

	int GetSSN(WeaponS *p);
	void ShowWeaponInfo(WeaponS *p);
	WeaponS *MakeWeaponData(int ssn, const char * name, int dam, int price);

	~Weapon();
};

