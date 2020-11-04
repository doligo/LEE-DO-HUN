#include "GameSystem.h"

GameSystem* GameSystem::game_system = NULL;

GameSystem::GameSystem()
{

}

void GameSystem::Init(HWND hWnd)
{
	B_A_D = new BitMap_And_Draw();
	B_A_D->Init_Bitmap(hWnd);
}

void GameSystem::Title_Screen()
{
	if (GetKeyState(VK_UP) & 0x8000)
		return;
}

GameSystem::~GameSystem()
{

}