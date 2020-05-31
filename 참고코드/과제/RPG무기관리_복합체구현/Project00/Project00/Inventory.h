#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <map>
using namespace std;


class Inventory
{
	Inventory* parent;
	const string nameis;

public:
	Inventory(string name);

	int pr_num = 1;

	virtual void View() = 0;
	virtual void AddInventory(Inventory* inventory) = 0;
	virtual void RemoveInventory(Inventory* inventory) = 0;

	void SetParent(Inventory* _parent);
	Inventory* GetParent();
	string GetName();
	int GetLevel();

protected:
	int GetSize();
};

class Bag : public Inventory
{
	// vector<Inventory*> inventoryList;
	map<int, Inventory*> inventoryList;
public:
	Bag(string name);
	~Bag();

	void View() override;
	void AddInventory(Inventory* inventory) override;
	void RemoveInventory(Inventory* inventory) override;
};

class Item : public Inventory
{
public:
	Item(string name);

	void View() override;
	void AddInventory(Inventory* inventory) {};
	void RemoveInventory(Inventory* inventory) {};
};