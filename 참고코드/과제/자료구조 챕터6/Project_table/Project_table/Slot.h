#include "User.h"
#pragma once

typedef int Key; // Ű��
typedef User_Info *Value; // Persons ����ü ������

enum SlotStatus // ���Ի���
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