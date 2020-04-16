#include "Person.h"
#pragma once

typedef int Key; // Ű���� �Ǵ� �ֹι�ȣ
typedef PersonS *Value; // Persons ����ü ������

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