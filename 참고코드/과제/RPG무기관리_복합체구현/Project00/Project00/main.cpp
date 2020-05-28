#include "Inventory.h"

#define MAX 10

int main()
{
	ifstream read;
	string tmp_st;

	Inventory *inven = new Bag("인벤토리");
	Inventory *bag = new Bag("장비창");
	
	read.open("wp.txt");
	if (!read)
	{
		cout << "파일이 존재하지않습니다" << endl;
		return 0;
	}
	else
	{
		while (!read.eof())
		{
			read >> tmp_st;
			Inventory *item = new Item(tmp_st);
			bag->AddInventory(item);
		}
	}
	read.close();

	inven->AddInventory(bag);
	Inventory *bag2 = new Bag("소비창");
	inven->AddInventory(bag2);

	inven->View();
	delete inven;

	return 0;
}

