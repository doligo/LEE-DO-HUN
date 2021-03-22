#include "GameManager.h"

GameManager* GameManager::SingleTone_GM = NULL;

GameManager::GameManager()
{

}

void GameManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	Bt_Draw = new BitMap_And_Draw;
	Bt_Draw->Init_Bitmap(hWnd);
	NT = new NetWork;
	NT->Init_Network(hWnd);

	m_hWnd = hWnd;
	m_hInst = hInstance;
	m_NameBox = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 640, 650, 120, 20, m_hWnd, (HMENU)200, m_hInst, NULL);

	m_select_character = Character_Orange;
	m_game_status = Status_Select_Character;
	m_my_mouse_x = 0;
	m_my_mouse_y = 0;

	Set_Select_Character_Pos();
}

void GameManager::Update(LPARAM lParam, WPARAM wParam)
{
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
		Bt_Draw->Draw_Detail_Ready(440, 370, Character_BeanCake, Character_BeanCake, 1, 1);
		Bt_Draw->Draw_Detail_Ready(547, 360, Character_Pepper, Character_Pepper, 1, 1);
		Bt_Draw->Draw_Detail_Ready(654, 380, Character_Salad, Character_Salad, 1, 1);
		Bt_Draw->Draw_Detail_Ready(753, 370, Character_Dong, Character_Dong, 1, 1);
		Bt_Draw->Draw_Detail_Ready(271, 488, Character_Garlic, Character_Garlic, 1, 1);
		Bt_Draw->Draw_Detail_Ready(380, 480, Character_MushRoom, Character_MushRoom, 1, 1);
		Bt_Draw->Draw_Detail_Ready(488, 493, Character_Banana, Character_Banana, 1, 1);
		Bt_Draw->Draw_Detail_Ready(592, 492, Character_Tomato, Character_Tomato, 1, 1);
		Bt_Draw->Draw_Detail_Ready(704, 495, Character_Grape, Character_Grape, 1, 1);

		Bt_Draw->Draw_Detail_Ready(502, 590, m_select_character, m_select_character, 15, 15);
		Bt_Draw->Draw_Go();
	}

	InvalidateRect(m_NameBox, FALSE, NULL); // << 이것때문에 마우스 인식이 잘안된다
	// 캐릭터선택창은 그냥 넘어가게하고 이름입력단계 화면을 하나 더 만들기 **
	Input(lParam, wParam);
}

void GameManager::Input(LPARAM lParam , WPARAM wParam)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		m_my_mouse_x = LOWORD(lParam);
		m_my_mouse_y = HIWORD(lParam);

		if (m_game_status == Status_Select_Character) // 캐릭터 선택창
		{
			for (int i = 0; i < 16; i++)
			{
				if (My_Character_Pos[i].rt.left <= m_my_mouse_x && My_Character_Pos[i].rt.top <= m_my_mouse_y && My_Character_Pos[i].rt.right >= m_my_mouse_x && My_Character_Pos[i].rt.bottom >= m_my_mouse_y)
					m_select_character = My_Character_Pos[i].name;
			}
		}
	}
	else if (GetAsyncKeyState(VK_RETURN) & 0x8001)	 //	WM_KEYDOWN
	{
		if (m_game_status == Status_Select_Character) // 캐릭터 선택창
		{

		}
	}
}

void GameManager::Set_Select_Character_Pos()
{
	My_Character_Pos[0].rt = { 271, 231, 344, 304 }; // 오렌지룽
	My_Character_Pos[0].name = Character_Orange;
	My_Character_Pos[1].rt = { 375, 241, 449, 307 }; // 완란룽
	My_Character_Pos[1].name = Character_Egg;
	My_Character_Pos[2].rt = { 483, 235, 557, 307 };
	My_Character_Pos[2].name = Character_Radish;
	My_Character_Pos[3].rt = { 584, 237, 664, 307 };
	My_Character_Pos[3].name = Character_EggHalf;
	My_Character_Pos[4].rt = { 700, 237, 764, 307 };
	My_Character_Pos[4].name = Character_Kimchi;
	My_Character_Pos[5].rt = { 220, 356, 299, 428 };
	My_Character_Pos[5].name = Character_RiceRock;
	My_Character_Pos[6].rt = { 324, 356, 405, 428 };
	My_Character_Pos[6].name = Character_Lettuce;
	My_Character_Pos[7].rt = { 429, 356, 507, 428 };
	My_Character_Pos[7].name = Character_BeanCake;
	My_Character_Pos[8].rt = { 536, 356, 615, 428 };
	My_Character_Pos[8].name = Character_Pepper;
	My_Character_Pos[9].rt = { 640, 356, 719, 428 };
	My_Character_Pos[9].name = Character_Salad;
	My_Character_Pos[10].rt = { 745, 356, 828, 428 };
	My_Character_Pos[10].name = Character_Dong;
	My_Character_Pos[11].rt = { 268, 481, 350, 551 };
	My_Character_Pos[11].name = Character_Garlic;
	My_Character_Pos[12].rt = { 374, 481, 454, 551 };
	My_Character_Pos[12].name = Character_MushRoom;
	My_Character_Pos[13].rt = { 479, 481, 558, 551 };
	My_Character_Pos[13].name = Character_Banana;
	My_Character_Pos[14].rt = { 584, 481, 665, 551 };
	My_Character_Pos[14].name = Character_Tomato;
	My_Character_Pos[15].rt = { 691, 481, 769, 551 };
	My_Character_Pos[15].name = Character_Grape;
}

GameManager::~GameManager()
{

}
