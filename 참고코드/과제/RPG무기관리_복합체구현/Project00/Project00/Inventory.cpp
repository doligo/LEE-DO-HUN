#include "Inventory.h"

Inventory::Inventory(string name) : nameis(name)
{
	parent = NULL;
}

void Inventory::SetParent(Inventory *_parent)
{
	parent = _parent;
}

Inventory* Inventory::GetParent()
{
	return parent;
}

string Inventory::GetName()
{
	return nameis;
}

int Inventory::GetLevel()
{
	int level = 0;
	Inventory *inven = GetParent();

	while (inven != NULL)
	{
		level++;
		inven = inven->GetParent();
	}

	return level;
}

int Inventory::GetSize()
{
	return nameis.size() + GetLevel() * 2;
}


////////////////// ������ Bag, item

Item::Item(string name) : Inventory(name)
{

}

void Item::View()
{
	cout << setiosflags(ios::right) << setw(GetSize());
	cout << setfill(' ') << GetName().c_str() << " - Item" << endl;
}

Bag::Bag(string name) : Inventory(name)
{
}

Bag::~Bag() // �Ҹ��ڿ� vector �����Ҵ�����
{
	inventoryList.clear();
}

void Bag::View()
{
	cout << setiosflags(ios::right) << setw(GetSize());
	cout << setfill(' ') << GetName().c_str() << " - Bag" << endl;

	map<int, Inventory*>::iterator begin = inventoryList.begin();
	map<int, Inventory*>::iterator end = inventoryList.end();


	while (begin != end)
	{
		//(*begin)->View();
		
		(*begin).second->View();

		begin++;
	}
}

void Bag::AddInventory(Inventory* inventory)
{

	inventory->SetParent(this);

	inventoryList.insert(pair<int, Inventory*>(pr_num, inventory));

	pr_num++;
}

void Bag::RemoveInventory(Inventory* inventory)
{
	map<int, Inventory*>::iterator remove = inventoryList.find(1);
	// map���� begin, end, ã�°����� �����ʰ� �ٷ� find() �޼ҵ带 ����

	if (remove != inventoryList.end())
	{
		inventoryList.erase(remove);
	}
}