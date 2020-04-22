#include "Person.h"

#pragma once

typedef int Key;
typedef PersonS *Value;

struct Slot
{
	Key key;
	Value val;
};
