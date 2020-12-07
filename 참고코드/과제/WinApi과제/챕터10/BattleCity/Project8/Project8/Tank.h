#include <Windows.h>
#include <iostream>
#include <string.h>
#pragma once

#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14

#define DEAD 0
#define ALIVE 1

class Tank
{
private:
	bool status;
	double m_ix;
	double m_iy;
	double m_pre_x;
	double m_pre_y;
	int direct;
	int player;
	int shield;
	int shield_motion;
	int motion;
	double speed;

public:
	Tank();

	int player_start_x;
	int player_start_y;
	int enemy_start_x;
	int enemy_start_y;
	int move_count;

	void Init_Tank(int player_or_enemy);
	void Moveing(int dir);
	int Get_Tank_X();
	int Get_Tank_Y();
	int Get_Tank_Direct();
	int Get_Tank_Motion();
	int Get_Player_Check();
	int Get_Status();
	void Set_Status(int value);
	void RollBack_pos();
	void Set_Tank_X(int num);
	void Set_Tank_Y(int num);
	bool Get_Tank_Shield();
	void Set_Tank_Shield(int value);
	int Get_Tank_Shield_Motion();
	void Set_Tank_Shield_Motion(int num);
	void Set_Tank_Speed(double num);
	void ReSet_Speed(int num);

	~Tank();
};

