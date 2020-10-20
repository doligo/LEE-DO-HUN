#include <Windows.h>
#include <iostream>
#include "Draw_And_Set.h"
#pragma once

using namespace std;

class GameSystem
{
private:
public:
	GameSystem();

	Draw_And_Set *D_A_S;
	int now_difficulty;
	void Init(HWND hWnd);
	void Game_Flow(HDC hdc);

	~GameSystem();
};

