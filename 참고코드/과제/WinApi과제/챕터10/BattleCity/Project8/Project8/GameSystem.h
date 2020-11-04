#include "BitMap_And_Draw.h"
using namespace std;

#pragma once
class GameSystem
{
private:
	static GameSystem *game_system;
	BitMap_And_Draw *B_A_D;
public:

	GameSystem();

	static GameSystem *GetInstane()
	{
		if (game_system == NULL)
			game_system = new GameSystem();
		return game_system;
	}

	void Init(HWND hWnd);
	void Title_Screen();

	~GameSystem();
};

