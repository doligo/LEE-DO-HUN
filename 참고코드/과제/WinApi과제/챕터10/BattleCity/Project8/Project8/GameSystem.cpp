#include "GameSystem.h"

GameSystem* GameSystem::game_system = NULL;

GameSystem::GameSystem()
{
	game_status = 0;
	game_keyboard = KEY_UP;
	game_stage = 1;
}

void GameSystem::Init(HWND hWnd)
{
	B_A_D = new BitMap_And_Draw();
	B_A_D->Init_Bitmap(hWnd);
	MP = new Map();
	MP->Init_Map(game_stage - 1);
	for (int i = 0; i < 5; i++)
	{
		TK[i] = new Tank();
		TK[i]->Init_Tank(i);
	}
}

void GameSystem::Title_Screen()
{
	if (game_keyboard == KEY_UP)
	{
		B_A_D->Draw(410, 50, TITLE_LOGO, TITLE_LOGO);
		B_A_D->Draw(520, 250, TITLE_MENU_01, TITLE_MENU_01);
		B_A_D->Draw(520, 350, TITLE_MENU_02, TITLE_MENU_02);

		B_A_D->Draw(400, 250, TITLE_MENU_03, TITLE_MENU_03);
		B_A_D->Draw(400, 350, TITLE_MENU_04, TITLE_MENU_04);
	}
	else if (game_keyboard == KEY_DOWN)
	{
		B_A_D->Draw(410, 50, TITLE_LOGO, TITLE_LOGO);
		B_A_D->Draw(520, 250, TITLE_MENU_01, TITLE_MENU_01);
		B_A_D->Draw(520, 350, TITLE_MENU_02, TITLE_MENU_02);

		B_A_D->Draw(400, 350, TITLE_MENU_03, TITLE_MENU_03);
		B_A_D->Draw(400, 250, TITLE_MENU_04, TITLE_MENU_04);
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		game_keyboard = KEY_UP;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		game_keyboard = KEY_DOWN;
	}
	else if (GetKeyState(VK_RETURN) & 0x8000)
	{
		if (game_keyboard == KEY_UP)
		{
			B_A_D->Draw_Black_BackGround(); // 타이틀화면 지우기
			game_status = GAME_START;
		}
		else if (game_keyboard == KEY_DOWN)
			game_status = GAME_EXIT;
	}
}

void GameSystem::Game_Screen()
{
	char value = NULL;
	int num = 0;

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			value = MP->Get_Map_Info(i, j);

			if (value == 'N')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, BLANK, BLANK);
			else if (value == 'B')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, N_BLOCK_00, N_BLOCK_00);
			else if (value == 'G')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, GRAY_BLOCK, GRAY_BLOCK);
			else if (value == 'b')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, BUSH_BLOCK, BUSH_BLOCK);
			else if (value == 'w')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, WATER_BLOCK, WATER_BLOCK);
			else if (value == 'W')
				B_A_D->Draw(WIDTH * j, HEIGHT * i, WHITE_BLOCK_00, WHITE_BLOCK_00);

			m_block_rt[num] = { WIDTH * j, HEIGHT * i, (WIDTH * j) + 33, (HEIGHT * i) + 25 };
			num++;
		}
	}
}

void GameSystem::Move()
{
	if (GetKeyState(VK_UP) & 0x8000)
	{

	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{

	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{

	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{

	}
}

void GameSystem::Enemy_Move()
{

}

GameSystem::~GameSystem()
{

}