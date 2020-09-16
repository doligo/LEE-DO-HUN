#include "GameSystem.h"

GameSystem::GameSystem()
{

}

void GameSystem::Init(HWND hWnd, HINSTANCE hlnst)
{
	BG = new BackGround();
	BG->Init_BackGround(hWnd, hlnst);
}

int GameSystem::Draw(HDC hdc)
{
	static int check = 0;

	if (check != 30)
		check = BG->Draw_TitleScreen(hdc);
	else
		BG->Draw_GameScreen(hdc);
	
	return 0;
}

GameSystem::~GameSystem()
{

}