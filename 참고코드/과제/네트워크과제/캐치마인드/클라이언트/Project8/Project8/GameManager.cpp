#include "GameManager.h"

GameManager* GameManager::SingleTone_GM = NULL;

GameManager::GameManager()
{

}

void GameManager::Init(HWND hWnd)
{
	Bt_Draw = new BitMap_And_Draw;
	Bt_Draw->Init_Bitmap(hWnd);
	NT = new NetWork;
	NT->Init_Network(hWnd);

	m_select_character = Character_Onion;
}

void GameManager::Update()
{
	Bt_Draw->Draw_Ready(0, 0, Select_Character_temp, Select_Character_temp);
	Bt_Draw->Draw_Detail_Ready(503, 590, m_select_character, m_select_character, 10, 10);
	Bt_Draw->Draw_Go();
}

GameManager::~GameManager()
{

}
