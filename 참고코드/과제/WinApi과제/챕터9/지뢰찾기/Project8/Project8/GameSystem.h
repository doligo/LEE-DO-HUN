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
	void Left_Click_Check(int x, int y);
	void Right_Click_Check(int x, int y);

	~GameSystem();
};

