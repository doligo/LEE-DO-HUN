#include "Table.h"

int GetHashValue(int n)
{
	return n % 100;
}

void Data_Load(Table *t, User_Info *u, int *key)
{
	int tmp_phone = 0;
	char tmp_name[STR_LEN] = {};
	char tmp_addr[STR_LEN] = {};
	int i = 0;
	int num = 110;

	ifstream read;
	read.open("데이터.txt");

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
			u = MakePersonData(tmp_phone, tmp_name, tmp_addr);
			key[i] = num;
			TBLInsert(t, key[i], u);

			i++;
			num += 5;
		}
		read.close();
	}

}

int main()
{
	Table *tb = new Table;
	User_Info *usr = new User_Info;
	int key[10] = {};
	int num = 0;

	TBLInit(tb, GetHashValue);
	Data_Load(tb, usr, key);

	cout << "가지고 있는 키값 : ";
	for (int i = 0; i < 9; i++)
	{
		if (key[i] == NULL)
		{
			break;
		}
		else
		cout << key[i] << " ";
	}
	cout << endl << endl;

	cout << "<모든 데이터 출력>" << endl << endl;

	for (int j = 0; j < 4; j++)
	{
		usr = TBLSearch(tb, key[j]);
		ShowPerInfo(usr);
	}

	cout << "삭제할 데이터의 키값을 입력하세요 : ";
	cin >> num;
	usr = TBLDelete(tb, num);
	free(usr);

	cout << endl;
	for (int j = 0; j < 4; j++)
	{
		usr = TBLSearch(tb, key[j]);
		if (usr == NULL)
		{
			cout << "삭제된 데이터입니다" << endl << endl;
		}
		else
		ShowPerInfo(usr);
	}

	return 0;
}
