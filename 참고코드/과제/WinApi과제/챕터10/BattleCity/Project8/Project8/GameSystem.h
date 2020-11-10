#include "BitMap_And_Draw.h"
#include "Map.h"
#include "Tank.h"
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
	RECT m_block_rt[BLOCK_MAX]; // rect는 시스템에서 관리하기가 편함
	RECT m_tank_rt;
public:

	GameSystem();

	int game_keyboard;
	int game_status;
	int game_stage;

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
	void Show_Tank();

	~GameSystem();
};

