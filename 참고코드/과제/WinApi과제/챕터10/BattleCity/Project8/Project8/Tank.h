#include <Windows.h>
#include <iostream>
#include <string.h>
#pragma once

#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14

class Tank
{
private:
	int m_ix;
	int m_iy;
	int direct;
	int player;
	int shield;
public:
	Tank();

	void Init_Tank(int player_or_enemy);
	void Moveing(int dir);
	void Shot();

	~Tank();
};

