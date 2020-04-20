#include "Table.h"
#include <fstream>
#include <string>
using namespace std;

int GetHashValue(int n)
{
	return n % 100;
}

void Data_Load(Table *t, User_Info *u, int *key)
{
	int tmp_phone = 0;
	string tmp_name;
	string tmp_addr;
	int i = 0;
	int num = 110;

	ifstream read;
	read.open("데이터임.txt");

	if (!read)
	{
		cout << "파일이 존재하지 않습니다" << endl;
		return;
	}
	else
	{
		while (!read.eof())
		{
			read >> tmp_phone;
			read >> tmp_name;
			read >> tmp_addr;
			//u = MakePersonData(tmp_phone, );
			key[i] = num;
			TBLInsert(t, key[i], u);

			i++;
			num += 5;
		}
	}
}

int main()
{
	Table *tb = new Table;
	User_Info *usr = new User_Info;
	int key[10] = {};

	TBLInit(tb, GetHashValue);
	Data_Load(tb, usr, key);


	return 0;
}
