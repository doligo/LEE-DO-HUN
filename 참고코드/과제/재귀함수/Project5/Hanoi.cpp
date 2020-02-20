#include "Hanoi.h"

void Hanoi::hanoi(int num, char from, char tmp, char to)
{
	if (num == 1)
	{
		cout << "원판 " << num << "을 " << from << "에서 " << to << "로 옮겼습니다" << endl;
	}
	else
	{
		hanoi(num - 1, from, to, tmp);
		cout << "원판 " << num << "을 " << from << "에서 " << to << "로 옮겼습니다" << endl;
		hanoi(num - 1, tmp, from, to);
	}
}