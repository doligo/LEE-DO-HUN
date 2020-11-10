#include <Windows.h>
#include <iostream>
#include <string.h>
#pragma once

class Tank
{
private:
	int m_ix;
	int m_iy;
public:
	Tank();

	void Init_Tank(int player_or_enemy);

	~Tank();
};

