#include "Inventory.h"


void Setting(string st, Inventory *bag_name)
{
	ifstream read;
	string tmp_st;

	read.open(st);
	if (!read)
	{
		cout << "파일이 존재하지않습니다" << endl;
		return;
	}
	else
	{
		while (!read.eof())
		{
			read >> tmp_st;
			Inventory* item = new Item(tmp_st);
			bag_name->AddInventory(item);
		}
	}
	read.close();
}

int main()
{
	ifstream read;
	string tmp_st;
	int select = 0;

	Inventory* inven = new Bag("인벤토리");
	Inventory* bag = new Bag("장비창");
	Inventory* bag2 = new Bag("소비창");
	Inventory* bag3 = new Bag("기타창");
	
	Setting("wp.txt", bag);
	Setting("ps.txt", bag2);
	Setting("etc.txt", bag3);

	inven->AddInventory(bag);
	inven->AddInventory(bag2);
	inven->AddInventory(bag3);

	while(1)
	{
		system("cls");

		cout << "1.장비창보기" << endl;
		cout << "2.소비창보기" << endl;
		cout << "3.기타창보기" << endl;
		cout << "4.전체보기" << endl;
		cout << "5.종료" << endl;
		cout << "입력 : ";

		cin >> select;
		switch (select)
		{
		case 1:
			system("cls");
			bag->View();
			system("pause");
			break;
		case 2:
			system("cls");
			bag2->View();
			system("pause");
			break;
		case 3:
			system("cls");
			bag3->View();
			system("pause");
			break;
		case 4:
			system("cls");
			inven->View();
			system("pause");
			break;
		case 5:
			return 0;
		}
	}

	delete inven;

	return 0;
}

