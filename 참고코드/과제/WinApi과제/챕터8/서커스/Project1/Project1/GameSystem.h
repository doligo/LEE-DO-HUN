#include "BackGround.h"
#pragma once
class GameSystem
{
private:
public:
	GameSystem();

	BackGround *BG;

	void Init(HWND hWnd, HINSTANCE hlnst);
	int Draw(HDC hdc);

	~GameSystem();
};

