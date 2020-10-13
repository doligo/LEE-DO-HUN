#include "GameSystem.h"

GameSystem::GameSystem()
{
	game_start_check = FALSE;
}

void GameSystem::Init(HWND hWnd, HINSTANCE hlnst)
{
	BG = new BackGround();
	BG->Init_BackGround(hWnd, hlnst);
	BG->Init_Player(hWnd, hlnst);
	BG->Init_Enemy(hWnd, hlnst);
}

int GameSystem::Draw(HDC hdc)
{
	static int check = 0;

	if (check != 30)
		check = BG->Draw_TitleScreen(hdc);
	else
	{
		if (BG->menu_select == 10)
		{
			if (game_start_check != TRUE)
			{
				BG->Draw_StageScreen(hdc);
				Sleep(1500);
				game_start_check = TRUE;
			}

			if (BG->die_check != TRUE && BG->clear_check == FALSE)
			{
				BG->Draw_GameScreen(hdc);
				BG->Control_Character();
			}
			else if (BG->die_check != TRUE && BG->clear_check == TRUE)
			{
				BG->Draw_Clear_Dance(hdc);
				//check = 0; // 메인화면으로 back
			}
			else
			{
				BG->Draw_Die_Character(hdc);
				Sleep(1500);
				game_start_check = FALSE;
				BG->die_check = FALSE;
				BG->Die_And_Init();
				BG->player_life -= 1;
				BG->player_score = 0;
			}

			if (BG->player_life == 0)
			{
				check = 0; // 메인화면으로 back
				BG->player_life = 5;
			}
			
		}
	}
	
	return 0;
}


GameSystem::~GameSystem()
{

}