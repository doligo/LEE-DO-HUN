#include "User.h"
#pragma once

typedef int Key; // Ű��
typedef PersonS *Value; // Persons ����ü ������

enum SlotStatus // ���Ի���
{
	EMPTY, // 0
	DELETED, // 1
	INUSE // 2
};