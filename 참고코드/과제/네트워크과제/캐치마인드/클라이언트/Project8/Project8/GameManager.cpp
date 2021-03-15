#include "GameManager.h"

GameManager* GameManager::SingleTone_GM = NULL;

GameManager::GameManager()
{
}

void GameManager::Init(HWND hWnd)
{
	Bt_Draw = new BitMap_And_Draw;
	Bt_Draw->Init_Bitmap(hWnd);
}

GameManager::~GameManager()
{
}
