#include "Person.h"
#pragma once

typedef int Key; // 키값이 되는 주민번호
typedef PersonS *Value; // Persons 구조체 변수값

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