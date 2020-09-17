#include "BackGround.h"
#pragma once
class GameSystem
{
private:
public:
	GameSystem();

	BackGround *BG;
	int game_start_check;

	void Init(HWND hWnd, HINSTANCE hlnst);
	int Draw(HDC hdc);

	~GameSystem();
};

