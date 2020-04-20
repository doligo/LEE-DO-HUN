#include "User.h"
#pragma once

typedef int Key; // 키값
typedef PersonS *Value; // Persons 구조체 변수값

enum SlotStatus // 슬롯상태
{
	EMPTY, // 0
	DELETED, // 1
	INUSE // 2
};