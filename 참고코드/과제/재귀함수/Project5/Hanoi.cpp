#include "Hanoi.h"

void Hanoi::hanoi(int num, char from, char tmp, char to)
{
	if (num == 1)
	{
		cout << "���� " << num << "�� " << from << "���� " << to << "�� �Ű���ϴ�" << endl;
	}
	else
	{
		hanoi(num - 1, from, to, tmp);
		cout << "���� " << num << "�� " << from << "���� " << to << "�� �Ű���ϴ�" << endl;
		hanoi(num - 1, tmp, from, to);
	}
}