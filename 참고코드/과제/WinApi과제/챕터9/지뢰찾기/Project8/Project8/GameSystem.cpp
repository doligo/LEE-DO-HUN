#include "GameSystem.h"

GameSystem::GameSystem()
{
	now_difficulty = 0;
}

void GameSystem::Init(HWND hWnd)
{
	D_A_S = new Draw_And_Set();

	if (now_difficulty == 0)
		D_A_S->difficulty = BEGINNER;
	else if (now_difficulty == 1)
		D_A_S->difficulty = INTERMEDIATE;
	else if (now_difficulty == 2)
		D_A_S->difficulty = ADVANCE;

	D_A_S->Init_BitMap(hWnd);
	D_A_S->Init_Game();
}

void GameSystem::Game_Flow(HDC hdc)
{
	D_A_S->Draw_Game_Screen(hdc);
}

GameSystem::~GameSystem()
{

}