#include "User.h"
#pragma once

typedef int Key; // 키값
typedef User_Info *Value; // Persons 구조체 변수값

enum SlotStatus // 슬롯상태
{
	EMPTY, // 0
	DELETED, // 1
	INUSE // 2
};

struct Slot
{
	Key key;
	Value val;
	SlotStatus status;
};