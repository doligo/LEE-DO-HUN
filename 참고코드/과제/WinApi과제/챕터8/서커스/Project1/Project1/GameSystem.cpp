#include "GameSystem.h"

GameSystem::GameSystem()
{

}

void GameSystem::Init(HWND hWnd, HINSTANCE hlnst)
{
	BG = new BackGround();
	BG->Init_BackGround(hWnd, hlnst);
}

void GameSystem::Draw(HDC hdc)
{
	BG->Draw_TitleScreen(hdc);
}

GameSystem::~GameSystem()
{

}