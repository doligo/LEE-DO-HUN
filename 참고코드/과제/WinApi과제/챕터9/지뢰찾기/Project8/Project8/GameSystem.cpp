#include "GameSystem.h"

GameSystem::GameSystem()
{

}

void GameSystem::Init(HWND hWnd)
{
	D_A_S = new Draw_And_Set();
	D_A_S->Init_BitMap(hWnd);
}

void GameSystem::Game_Flow(HDC hdc)
{
	D_A_S->Draw_Game_Screen(hdc);
}

GameSystem::~GameSystem()
{

}