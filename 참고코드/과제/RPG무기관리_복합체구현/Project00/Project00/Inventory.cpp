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


////////////////// 밑으로 Bag, item

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

Bag::~Bag() // 소멸자에 vector 동적할당해제
{
	inventoryList.clear();
}

void Bag::View()
{
	cout << setiosflags(ios::right) << setw(GetSize());
	cout << setfill(' ') << GetName().c_str() << " - Bag" << endl;

	vector<Inventory*>::iterator begin = inventoryList.begin();
	vector<Inventory*>::iterator end = inventoryList.end();

	while (begin != end)
	{
		(*begin)->View();

		begin++;
	}
}

void Bag::AddInventory(Inventory* inventory)
{

	inventory->SetParent(this);
	inventoryList.push_back(inventory);
}

void Bag::RemoveInventory(Inventory* inventory)
{
	vector<Inventory*>::iterator remove = find(inventoryList.begin(), inventoryList.end(), inventory);

	if (remove != inventoryList.end())
	{
		inventoryList.erase(remove);
	}
}