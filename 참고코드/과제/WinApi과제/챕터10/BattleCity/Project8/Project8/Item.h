#include <iostream>
#include <Windows.h>
#include <string.h>
#pragma once

struct _Item
{
	int item_x;
	int item_y;
	// string item_name;
};

class Item
{
private:
public:
	Item();

	void Init_Item();

	~Item();
};

