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
	B_A_D->Draw(400, 300, 1, 1);
}

GameSystem::~GameSystem()
{

}