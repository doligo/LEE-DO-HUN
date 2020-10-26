#include "GameSystem.h"

GameSystem::GameSystem()
{
	now_difficulty = 0;
	check_game_start = FALSE;
	game_time = 0;
	game_over = FALSE;
	game_clear = FALSE;
}

void GameSystem::Init(HWND hWnd)
{
	check_game_start = FALSE;
	game_over = FALSE;
	game_clear = FALSE;

	D_A_S = new Draw_And_Set();

	if (now_difficulty == 0)
		D_A_S->difficulty = BEGINNER;
	else if (now_difficulty == 1)
		D_A_S->difficulty = INTERMEDIATE;
	else if (now_difficulty == 2)
		D_A_S->difficulty = ADVANCE;

	D_A_S->Init_BitMap(hWnd);
	D_A_S->Init_Game();
}

void GameSystem::Game_Flow(HDC hdc, HWND hWnd)
{
	if (game_over == FALSE && game_clear == FALSE)
	{
		D_A_S->Draw_Game_Screen(hdc, hWnd);
		if (D_A_S->start_game == TRUE)
			check_game_start = TRUE;
		else
			check_game_start = FALSE;
	}
	else if (game_over == TRUE || game_clear == TRUE)
	{
		D_A_S->Draw_All_Mine(hdc);
	}
}

void GameSystem::Left_Click_Check(int x, int y)
{
	int check = 0;

	D_A_S->Left_Click(x, y);
	check = D_A_S->Left_Click_Mine(x, y);

	if (check == TRUE)
		game_over = TRUE;
	if (D_A_S->clear_trigger == TRUE)
		game_clear = TRUE;
}

void GameSystem::Right_Click_Check(int x, int y)
{
	D_A_S->Right_Click(x, y);
}

void GameSystem::Show_Time(HWND _hWnd)
{
	char buffer[256] = {};

	if (D_A_S->difficulty == BEGINNER)
	{
		RECT rt = { 25, 355, 25 + 100, 355 + 20 };
		game_time++;
		sprintf_s(buffer, "%d", game_time);
		DrawText(GetDC(_hWnd), buffer, -1, &rt, DT_CENTER | DT_WORDBREAK);
	}
	else if (D_A_S->difficulty == INTERMEDIATE)
	{
		RECT rt = { 83, 640, 83 + 100, 640 + 20 };
		game_time++;
		sprintf_s(buffer, "%d", game_time);
		DrawText(GetDC(_hWnd), buffer, -1, &rt, DT_CENTER | DT_WORDBREAK);
	}
	else if (D_A_S->difficulty == ADVANCE)
	{
		RECT rt = { 200, 640, 200 + 100, 640 + 20 };
		game_time++;
		sprintf_s(buffer, "%d", game_time);
		DrawText(GetDC(_hWnd), buffer, -1, &rt, DT_CENTER | DT_WORDBREAK);
	}
}

GameSystem::~GameSystem()
{

}