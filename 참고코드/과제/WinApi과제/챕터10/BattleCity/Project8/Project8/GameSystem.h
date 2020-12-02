#include "BitMap_And_Draw.h"
#include "Map.h"
#include "Tank.h"
#include "Missile.h"
#include "Item.h"
using namespace std;
#pragma once

#define KEY_UP 10
#define KEY_DOWN 20

#define GAME_START 30
#define GAME_OVER 40
#define GAME_EXIT 50

#define BLOCK_MAX 784

class GameSystem
{
private:
	static GameSystem *game_system;
	BitMap_And_Draw *B_A_D;
	Map *MP;
	Tank *TK[5];
	RECT m_block_rt[BLOCK_MAX]; // rect�� �ý��ۿ��� �����ϱⰡ ����
	RECT m_tank_rt[5];

	Missile *PLAYER_ME[3];
	Missile *ME[4];
	RECT m_player_missile_rt[3];
	RECT m_missile_rt[4];

	RECT m_explosion_rt[5];

	Item *IT;
public:

	GameSystem();

	int game_keyboard;
	int game_status;
	int game_stage;
	int player_life;

	int cur_time;
	int move_time;
	int missile_time;
	int player_explosion_time;
	int explosion_time[4];
	int shield_time[5];

	int player_missile_on[3];
	int missile_on[4];

	int explosion_motion;

	static GameSystem *GetInstane()
	{
		if (game_system == NULL)
			game_system = new GameSystem();
		return game_system;
	}

	void Init(HWND hWnd);
	void Title_Screen();
	void Game_Screen();
	void Control_Tank();
	void Show_Map();
	void Show_Bush();
	int Show_Tank();
	void Show_Shield();
	void Show_Missile();
	int Check_Block_Tank(int num);
	int Create_Tank();
	void Set_Enemy_Pos(int num);
	void Set_Missile_Start();
	void Set_Missile_Rt();
	void Missile_End_Check();
	void Player_Missile_Dead(int num);
	void Missile_Dead(int num);
	int Block_Collision(int num);
	void Tank_Collision();
	void Tank_Dead(int num);
	void Missile_Collision();
	void Show_Tank_Collision();
	void On_Shield(int num);
	void Off_Shield(int num);
	void Set_Item();
	

	~GameSystem();
};

