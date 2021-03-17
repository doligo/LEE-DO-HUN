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
	m_game_status = Status_Select_Character;
	m_my_mouse_x = 0;
	m_my_mouse_y = 0;
}

void GameManager::Update()
{
	if (WM_LBUTTONDOWN)

	if (m_game_status == Status_Select_Character)
	{
		Bt_Draw->Draw_Ready(0, 0, Select_Character, Select_Character);
		Bt_Draw->Draw_Ready(93, 79, Button_join, Button_join);
		Bt_Draw->Draw_Ready(6, 79, Button_exit, Button_exit);
		Bt_Draw->Draw_Ready(270, 318, Select_Character_Name1, Select_Character_Name1);
		Bt_Draw->Draw_Ready(223, 436, Select_Character_Name2, Select_Character_Name2);
		Bt_Draw->Draw_Ready(276, 560, Select_Character_Name3, Select_Character_Name3);

		Bt_Draw->Draw_Detail_Ready(278, 242, Character_Orange, Character_Orange, 1, 1);
		Bt_Draw->Draw_Detail_Ready(390, 247, Character_Egg, Character_Egg, 1, 1);
		Bt_Draw->Draw_Detail_Ready(495, 242, Character_Radish, Character_Radish, 1, 1);
		Bt_Draw->Draw_Detail_Ready(600, 247, Character_EggHalf, Character_EggHalf, 1, 1);
		Bt_Draw->Draw_Detail_Ready(700, 245, Character_Kimchi, Character_Kimchi, 1, 1);
		Bt_Draw->Draw_Detail_Ready(235, 370, Character_RiceRock, Character_RiceRock, 1, 1);
		Bt_Draw->Draw_Detail_Ready(333, 370, Character_Lettuce, Character_Lettuce, 1, 1);
		Bt_Draw->Draw_Detail_Ready2(440, 370, Character_BeanCake, Character_BeanCake, 1, 1);
		Bt_Draw->Draw_Detail_Ready(547, 360, Character_Pepper, Character_Pepper, 1, 1);
		Bt_Draw->Draw_Detail_Ready(654, 380, Character_Salad, Character_Salad, 1, 1);
		Bt_Draw->Draw_Detail_Ready(753, 370, Character_Dong, Character_Dong, 1, 1);
		Bt_Draw->Draw_Detail_Ready(271, 488, Character_Garlic, Character_Garlic, 1, 1);
		Bt_Draw->Draw_Detail_Ready(380, 480, Character_MushRoom, Character_MushRoom, 1, 1);
		Bt_Draw->Draw_Detail_Ready2(488, 493, Character_Banana, Character_Banana, 1, 1);
		Bt_Draw->Draw_Detail_Ready(592, 492, Character_Tomato, Character_Tomato, 1, 1);
		Bt_Draw->Draw_Detail_Ready(704, 495, Character_Grape, Character_Grape, 1, 1);

		Bt_Draw->Draw_Detail_Ready(503, 590, m_select_character, m_select_character, 10, 10);
		Bt_Draw->Draw_Go();
	}
}

void GameManager::Input_Mouse(LPARAM lParam)
{
	m_my_mouse_x = LOWORD(lParam);
	m_my_mouse_y = HIWORD(lParam);
}

GameManager::~GameManager()
{

}
