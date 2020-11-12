#include "GameSystem.h"

GameSystem* GameSystem::game_system = NULL;

GameSystem::GameSystem()
{
	game_status = 0;
	game_keyboard = KEY_UP;
	game_stage = 1;
	player_life = 4;
}

void GameSystem::Init(HWND hWnd)
{
	B_A_D = new BitMap_And_Draw();
	B_A_D->Init_Bitmap(hWnd);

	MP = new Map();
	MP->Init_Map(game_stage - 1);

	for (int i = 0; i < 5; i++)
	{
		TK[i] = new Tank(); // 탱크생성
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
	Create_Tank();

	//////////////////////////////////////////////////

	Show_Map();
	Show_Tank();
	Show_Bush();
	B_A_D->Draw_Go(); // 일반 draw함수는 렉때문에 TransparentBlt을 먼저 쓴후 BitBlt으로 출력하게 함 (draw_ready로 긁어서 draw_go로 뿌리기)

	Control_Tank();
}

void GameSystem::Control_Tank()
{
	int result = 0;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		result = Check_Block_Tank();
		if (result == 0)
			TK[0]->Moveing(UP);
		else
			TK[0]->RollBack_pos();
		// 블럭과 부딫치는지 비교, 맵끝인지 비교 후 moving으로 가게하기
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		result = Check_Block_Tank();
		if (result == 0)
			TK[0]->Moveing(DOWN);
		else
			TK[0]->RollBack_pos();
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		result = Check_Block_Tank();
		if (result == 0)
			TK[0]->Moveing(LEFT);
		else
			TK[0]->RollBack_pos();
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		result = Check_Block_Tank();
		if (result == 0)
			TK[0]->Moveing(RIGHT);
		else
			TK[0]->RollBack_pos();
	}
	else if (GetKeyState(VK_SPACE) & 0x8000)
	{
		TK[0]->Shot();
		// 총알나가게 하는 함수
	}

	m_tank_rt[0] = { 400 + TK[0]->Get_Tank_X(), 600 + TK[0]->Get_Tank_Y(), 400 + TK[0]->Get_Tank_X() + 28, 600 + TK[0]->Get_Tank_Y() + 20 };
	//// tank rect는 블럭보다 right와 bottom이 5씩 작다
}

void GameSystem::Show_Map()
{
	char value = NULL;
	int num = 0;

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			value = MP->Get_Map_Info(i, j);

			if (value == 'N')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, BLANK, BLANK);
			else if (value == 'B')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, N_BLOCK_00, N_BLOCK_00);
			else if (value == 'G')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, GRAY_BLOCK, GRAY_BLOCK);
			else if (value == 'w')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, WATER_BLOCK, WATER_BLOCK);
			else if (value == 'W')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, WHITE_BLOCK_00, WHITE_BLOCK_00);

			m_block_rt[num] = { WIDTH * j, HEIGHT * i, (WIDTH * j) + 33, (HEIGHT * i) + 25 };
			num++;
		}
	}
}

void GameSystem::Show_Bush()
{
	char value;

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			value = MP->Get_Map_Info(i, j);
			if (value == 'b')
				B_A_D->Draw_Ready(WIDTH * j, HEIGHT * i, BUSH_BLOCK, BUSH_BLOCK);
		}
	}
}

int GameSystem::Show_Tank()
{
	if (TK[0]->Get_Player_Check() == TRUE && TK[0]->Get_Status() == ALIVE)
	{
		if (UP == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(400 + TK[0]->Get_Tank_X(), 600 + TK[0]->Get_Tank_Y(), PLAYER_UP_00 + TK[0]->Get_Tank_Motion(), PLAYER_UP_00 + TK[0]->Get_Tank_Motion());
		else if (DOWN == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(400 + TK[0]->Get_Tank_X(), 600 + TK[0]->Get_Tank_Y(), PLAYER_DONW_00 + TK[0]->Get_Tank_Motion(), PLAYER_DONW_00 + TK[0]->Get_Tank_Motion());
		else if (LEFT == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(400 + TK[0]->Get_Tank_X(), 600 + TK[0]->Get_Tank_Y(), PLAYER_LEFT_00 + TK[0]->Get_Tank_Motion(), PLAYER_LEFT_00 + TK[0]->Get_Tank_Motion());
		else if (RIGHT == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(400 + TK[0]->Get_Tank_X(), 600 + TK[0]->Get_Tank_Y(), PLAYER_RIGHT_00 + TK[0]->Get_Tank_Motion(), PLAYER_RIGHT_00 + TK[0]->Get_Tank_Motion());
	}

	return 0;
}

int GameSystem::Check_Block_Tank()
{
	RECT temp;
	int num = 0;
	char tmp;

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			tmp = MP->Get_Map_Info(i, j);
			if (IntersectRect(&temp, &m_tank_rt[0], &m_block_rt[num]) && tmp != 'N' && tmp != 'b')
				return 1;
			num++;
		}
	}

	return 0;
}

int GameSystem::Create_Tank()
{
	if (TK[0]->Get_Status() == DEAD)
	{
		TK[0]->Set_Status(ALIVE);
		player_life--;
	}

	//// ** clock() 함수로 적 생성하기 
	return 0;
}

GameSystem::~GameSystem()
{

}