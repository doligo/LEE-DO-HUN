#include "Table.h"

int MyHashFunc(int n)
{
	return n % 100;
}

int main(void)
{
	Table TB;
	Weapon WP;

	TableS tbs;
	ifstream read;

	TB.TBLInit(&tbs, MyHashFunc);
	read.open("WeaponList.txt");

	if (!read)
	{
		cout << "파일이 존재하지않습니다" << endl;
		return;
	}



	return 0;
}