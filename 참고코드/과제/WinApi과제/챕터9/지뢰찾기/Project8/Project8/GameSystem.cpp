#include "GameSystem.h"

GameSystem::GameSystem()
{

}

void GameSystem::Init(HWND hWnd)
{
	D_A_S = new Draw_And_Set();
	D_A_S->Init_BitMap(hWnd);
}

GameSystem::~GameSystem()
{

}