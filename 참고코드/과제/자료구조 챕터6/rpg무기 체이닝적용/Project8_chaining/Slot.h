#include "Weapon.h"

#pragma once

typedef int Key;
typedef WeaponS *Value;

struct Slot
{
	Key key;
	Value val;
};
