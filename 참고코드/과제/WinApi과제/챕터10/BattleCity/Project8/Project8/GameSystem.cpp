#include "GameSystem.h"

GameSystem* GameSystem::game_system = NULL;

GameSystem::GameSystem()
{
	game_status = 0;
	game_keyboard = KEY_UP;
	game_stage = 1;
	player_life = 4;
	cur_time = 0;
	move_time = 0;

	for (int i = 0; i < 5; i++)
	{
		missile_on[i] = FALSE;
	}

	for (int i = 0; i < 5; i++)
	{
		m_tank_rt[i] = { 0,0,0,0 };
		m_missile_rt[i] = { 0,0,0,0 };
	}
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
		ME[i] = new Missile(); // 미사일생성
		ME[i]->Init_Missile(i);
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
	Show_Map();
	Create_Tank();
	Show_Tank();
	Show_Bush();
	Show_Missile();
	B_A_D->Draw_Go(); // 일반 draw함수는 렉때문에 TransparentBlt을 먼저 쓴후 BitBlt으로 출력하게 함 (draw_ready로 긁어서 draw_go로 뿌리기)

	Control_Tank();
}

void GameSystem::Control_Tank()
{
	int result = 0;
	int key = 0;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		result = Check_Block_Tank(0);
		if (result == 0)
			TK[0]->Moveing(UP);
		else
			TK[0]->RollBack_pos();
		// 블럭과 부딫치는지 비교, 맵끝인지 비교 후 moving으로 가게하기
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		result = Check_Block_Tank(0);
		if (result == 0)
			TK[0]->Moveing(DOWN);
		else
			TK[0]->RollBack_pos();
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		result = Check_Block_Tank(0);
		if (result == 0)
			TK[0]->Moveing(LEFT);
		else
			TK[0]->RollBack_pos();
	 }
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		result = Check_Block_Tank(0);
		if (result == 0)
			TK[0]->Moveing(RIGHT);
		else
			TK[0]->RollBack_pos();
	}
	else if (GetKeyState(VK_SPACE) & 0x8000)
	{
		missile_on[0] = TRUE;
	}
	if (missile_on[0] == TRUE)
		ME[0]->Move_Missile(TK[0]->Get_Tank_Direct());

	m_tank_rt[0] = { TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), TK[0]->player_start_x + TK[0]->Get_Tank_X() + 28, TK[0]->player_start_y + TK[0]->Get_Tank_Y() + 20 };

	////////////////// 이밑은 enemy

	if (clock() - move_time >= 10)
	{
		for (int i = 1; i < 5; i++)
		{
			if (TK[i]->Get_Status() == ALIVE)
			{
				key = rand() % 4 + 11;

				result = Check_Block_Tank(i);
				if (result == 0)
					TK[i]->Moveing(key);
				else
					TK[i]->RollBack_pos();
			}
			m_tank_rt[i] = { TK[i]->enemy_start_x + TK[i]->Get_Tank_X(), TK[i]->enemy_start_y + TK[i]->Get_Tank_Y(), TK[i]->enemy_start_x + TK[i]->Get_Tank_X() + 28, TK[i]->enemy_start_y + TK[i]->Get_Tank_Y() + 20 };
		}
		move_time = clock();
	}

	for (int i = 1; i < 5; i++)
	{
		if (missile_on[i] == TRUE)
			ME[i]->Move_Missile(TK[i]->Get_Tank_Direct());
	}

	///////////////// 이밑은 미사일관련함수

	Set_Missile_Start(); // (GetKeyState(VK_SPACE) & 0x8000) 입력됬을 경우 미사일설정
	Set_Missile_Rt(); // 미사일 rt를 매번 업데이트
	Missile_End_Check(); // 미사일 맵밖으로 나간것 체크
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
			B_A_D->Draw_Ready(TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), PLAYER_UP_00 + TK[0]->Get_Tank_Motion(), PLAYER_UP_00 + TK[0]->Get_Tank_Motion());
		else if (DOWN == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), PLAYER_DONW_00 + TK[0]->Get_Tank_Motion(), PLAYER_DONW_00 + TK[0]->Get_Tank_Motion());
		else if (LEFT == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), PLAYER_LEFT_00 + TK[0]->Get_Tank_Motion(), PLAYER_LEFT_00 + TK[0]->Get_Tank_Motion());
		else if (RIGHT == TK[0]->Get_Tank_Direct())
			B_A_D->Draw_Ready(TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), PLAYER_RIGHT_00 + TK[0]->Get_Tank_Motion(), PLAYER_RIGHT_00 + TK[0]->Get_Tank_Motion());
	}

	for (int i = 1; i < 5; i++)
	{
		if (TK[i]->Get_Status() == ALIVE)
		{
			if (UP == TK[i]->Get_Tank_Direct())
				B_A_D->Draw_Ready(TK[i]->enemy_start_x + TK[i]->Get_Tank_X(), TK[i]->enemy_start_y + TK[i]->Get_Tank_Y(), ENEMY_UP_00 + TK[i]->Get_Tank_Motion(), ENEMY_UP_00 + TK[i]->Get_Tank_Motion());
			else if (DOWN == TK[i]->Get_Tank_Direct())
				B_A_D->Draw_Ready(TK[i]->enemy_start_x + TK[i]->Get_Tank_X(), TK[i]->enemy_start_y + TK[i]->Get_Tank_Y(), ENEMY_DOWN_00 + TK[i]->Get_Tank_Motion(), ENEMY_DOWN_00 + TK[i]->Get_Tank_Motion());
			else if (LEFT == TK[i]->Get_Tank_Direct())
				B_A_D->Draw_Ready(TK[i]->enemy_start_x + TK[i]->Get_Tank_X(), TK[i]->enemy_start_y + TK[i]->Get_Tank_Y(), ENEMY_LEFT_00 + TK[i]->Get_Tank_Motion(), ENEMY_LEFT_00 + TK[i]->Get_Tank_Motion());
			else if (RIGHT == TK[i]->Get_Tank_Direct())
				B_A_D->Draw_Ready(TK[i]->enemy_start_x + TK[i]->Get_Tank_X(), TK[i]->enemy_start_y + TK[i]->Get_Tank_Y(), ENEMY_RIGHT_00 + TK[i]->Get_Tank_Motion(), ENEMY_RIGHT_00 + TK[i]->Get_Tank_Motion());
		}
	}

	return 0;
}

void GameSystem::Show_Missile()
{
	if (ME[0]->Get_Missile_Player() == TRUE && ME[0]->Get_Missile_Status() == TRUE)
	{
		if (UP == ME[0]->Get_Missile_Direct())
			B_A_D->Draw_Ready(ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), MISSILE_UP, MISSILE_UP);
		else if (DOWN == ME[0]->Get_Missile_Direct())
			B_A_D->Draw_Ready(ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), MISSILE_DOWN, MISSILE_DOWN);
		else if (LEFT == ME[0]->Get_Missile_Direct())
			B_A_D->Draw_Ready(ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), MISSILE_LEFT, MISSILE_LEFT);
		else if (RIGHT == ME[0]->Get_Missile_Direct())
			B_A_D->Draw_Ready(ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), MISSILE_RIGHT, MISSILE_RIGHT);
	}

	for (int i = 1; i < 5; i++)
	{
		if (ME[i]->Get_Missile_Player() == TRUE && ME[i]->Get_Missile_Status() == TRUE)
		{
			if (UP == ME[i]->Get_Missile_Direct())
				B_A_D->Draw_Ready(ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), MISSILE_UP, MISSILE_UP);
			else if (DOWN == ME[i]->Get_Missile_Direct())
				B_A_D->Draw_Ready(ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), MISSILE_DOWN, MISSILE_DOWN);
			else if (LEFT == ME[i]->Get_Missile_Direct())
				B_A_D->Draw_Ready(ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), MISSILE_LEFT, MISSILE_LEFT);
			else if (RIGHT == ME[i]->Get_Missile_Direct())
				B_A_D->Draw_Ready(ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), MISSILE_RIGHT, MISSILE_RIGHT);
		}
	}
}

int GameSystem::Check_Block_Tank(int num)
{
	RECT temp;
	int _num = 0;
	char tmp;

	if (num == 0)
	{
		for (int i = 0; i < MAP_MAX; i++)
		{
			for (int j = 0; j < MAP_MAX; j++)
			{
				tmp = MP->Get_Map_Info(i, j);
				if (IntersectRect(&temp, &m_tank_rt[num], &m_block_rt[_num]) && tmp != 'N' && tmp != 'b')
					return 1;
				else if (0 >= m_tank_rt[num].left || 0 >= m_tank_rt[num].top || 921 <= m_tank_rt[num].right || 698 <= m_tank_rt[num].bottom)
					return 1;
				_num++;
			}
		}
	}
	else if (num > 0)
	{
		for (int i = 0; i < MAP_MAX; i++)
		{
			for (int j = 0; j < MAP_MAX; j++)
			{
				tmp = MP->Get_Map_Info(i, j);
				if (IntersectRect(&temp, &m_tank_rt[num], &m_block_rt[_num]) && tmp != 'N' && tmp != 'b')
					return 1;
				else if (0 >= m_tank_rt[num].left || 0 >= m_tank_rt[num].top || 920 <= m_tank_rt[num].right || 698 <= m_tank_rt[num].bottom)
					return 1;
				_num++;
			}
		}
	}

	return 0;
}

int GameSystem::Create_Tank()
{
	if (TK[0]->Get_Status() == DEAD)
	{
		TK[0]->Set_Status(ALIVE);
		m_tank_rt[0] = { TK[0]->player_start_x + TK[0]->Get_Tank_X(), TK[0]->player_start_y + TK[0]->Get_Tank_Y(), TK[0]->player_start_x + TK[0]->Get_Tank_X() + 28, TK[0]->player_start_y + TK[0]->Get_Tank_Y() + 20 };
		//// tank rect는 블럭보다 right와 bottom이 5씩 작다
		player_life--;
	}

	if (clock() - cur_time >= 2500)
	{
		for (int i = 1; i < 5; i++)
		{
			if (TK[i]->Get_Status() == DEAD)
			{
				TK[i]->Set_Status(ALIVE);
				Set_Enemy_Pos(i);
				break;
			}
		}
		cur_time = clock();
	}

	return 0;
}

void GameSystem::Set_Enemy_Pos(int num)
{
	char tmp;
	int tmp_x = 0;
	int tmp_y = 0;
	int value = 0;
	int trigger = FALSE;

	while (1)
	{
		trigger = FALSE;
		value = rand() % 28;
		tmp = MP->Get_Map_Info(0, value);

		if (tmp == 'N')
		{
			for (int i = 1; i < 5; i++)
			{
				if (m_tank_rt[i].left == m_block_rt[value].left && m_tank_rt[i].top == m_block_rt[value].top)
					trigger = TRUE;
			}

			if (trigger == FALSE)
			{
				m_tank_rt[num] = { m_block_rt[value].left, m_block_rt[value].top + 2, m_block_rt[value].left + 28, m_block_rt[value].top + 2 + 20};
				TK[num]->enemy_start_x = m_tank_rt[num].left;
				TK[num]->enemy_start_y = m_tank_rt[num].top;
				break;
			}
		}
	}
}

void GameSystem::Set_Missile_Start()
{
	if (ME[0]->Get_Missile_Status() == FALSE)
	{
		if (TK[0]->Get_Tank_Direct() == UP)
		{
			ME[0]->missile_start_x = m_tank_rt[0].left + 13;
			ME[0]->missile_start_y = m_tank_rt[0].top;
		}
		else if (TK[0]->Get_Tank_Direct() == DOWN)
		{
			ME[0]->missile_start_x = m_tank_rt[0].left + 15;
			ME[0]->missile_start_y = m_tank_rt[0].top + 16;
		}
		else if (TK[0]->Get_Tank_Direct() == LEFT)
		{
			ME[0]->missile_start_x = m_tank_rt[0].left + 5;
			ME[0]->missile_start_y = m_tank_rt[0].top + 12;
		}
		else if (TK[0]->Get_Tank_Direct() == RIGHT)
		{
			ME[0]->missile_start_x = m_tank_rt[0].left + 19;
			ME[0]->missile_start_y = m_tank_rt[0].top + 9;
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if (ME[i]->Get_Missile_Status() == FALSE)
		{
			if (TK[i]->Get_Tank_Direct() == UP)
			{
				ME[i]->missile_start_x = m_tank_rt[i].left + 13;
				ME[i]->missile_start_y = m_tank_rt[i].top;
			}
			else if (TK[i]->Get_Tank_Direct() == DOWN)
			{
				ME[i]->missile_start_x = m_tank_rt[i].left + 15;
				ME[i]->missile_start_y = m_tank_rt[i].top + 16;
			}
			else if (TK[i]->Get_Tank_Direct() == LEFT)
			{
				ME[i]->missile_start_x = m_tank_rt[i].left + 5;
				ME[i]->missile_start_y = m_tank_rt[i].top + 12;
			}
			else if (TK[i]->Get_Tank_Direct() == RIGHT)
			{
				ME[i]->missile_start_x = m_tank_rt[i].left + 19;
				ME[i]->missile_start_y = m_tank_rt[i].top + 9;
			}
		}

		if (TK[i]->Get_Status() == ALIVE)
		{
			missile_on[i] = TRUE;
			cur_time = clock();
		}
	}
}

void GameSystem::Set_Missile_Rt()
{
	if (ME[0]->Get_Missile_Status() == TRUE)
	{
		if (TK[0]->Get_Tank_Direct() == UP)
			m_missile_rt[0] = { ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), ME[0]->missile_start_x + ME[0]->Get_Missile_X() + 10, ME[0]->missile_start_y + ME[0]->Get_Missile_Y() + 7 };
		else if (TK[0]->Get_Tank_Direct() == DOWN)
			m_missile_rt[0] = { ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), ME[0]->missile_start_x + ME[0]->Get_Missile_X() + 10, ME[0]->missile_start_y + ME[0]->Get_Missile_Y() + 7 };
		else if (TK[0]->Get_Tank_Direct() == LEFT)
			m_missile_rt[0] = { ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), ME[0]->missile_start_x + ME[0]->Get_Missile_X() + 10, ME[0]->missile_start_y + ME[0]->Get_Missile_Y() + 7 };
		else if (TK[0]->Get_Tank_Direct() == RIGHT)
			m_missile_rt[0] = { ME[0]->missile_start_x + ME[0]->Get_Missile_X(), ME[0]->missile_start_y + ME[0]->Get_Missile_Y(), ME[0]->missile_start_x + ME[0]->Get_Missile_X() + 10, ME[0]->missile_start_y + ME[0]->Get_Missile_Y() + 7 };
	}

	for (int i = 1; i < 5; i++)
	{
		if (ME[i]->Get_Missile_Status() == TRUE)
		{
			if (TK[i]->Get_Tank_Direct() == UP)
				m_missile_rt[i] = { ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), ME[i]->missile_start_x + ME[i]->Get_Missile_X() + 10, ME[i]->missile_start_y + ME[i]->Get_Missile_Y() + 7 };
			else if (TK[i]->Get_Tank_Direct() == DOWN)
				m_missile_rt[i] = { ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), ME[i]->missile_start_x + ME[i]->Get_Missile_X() + 10, ME[i]->missile_start_y + ME[i]->Get_Missile_Y() + 7 };
			else if (TK[i]->Get_Tank_Direct() == LEFT)
				m_missile_rt[i] = { ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), ME[i]->missile_start_x + ME[i]->Get_Missile_X() + 10, ME[i]->missile_start_y + ME[i]->Get_Missile_Y() + 7 };
			else if (TK[i]->Get_Tank_Direct() == RIGHT)
				m_missile_rt[i] = { ME[i]->missile_start_x + ME[i]->Get_Missile_X(), ME[i]->missile_start_y + ME[i]->Get_Missile_Y(), ME[i]->missile_start_x + ME[i]->Get_Missile_X() + 10, ME[i]->missile_start_y + ME[i]->Get_Missile_Y() + 7 };
		}
	}
}

void GameSystem::Missile_End_Check()
{
	if (ME[0]->Get_Missile_Status() == TRUE)
	{
		if (0 >= m_missile_rt[0].left || 0 >= m_missile_rt[0].top || 920 <= m_missile_rt[0].right || 698 <= m_missile_rt[0].bottom)
		{
			missile_on[0] = FALSE;
			ME[0]->Set_Missile_Status(FALSE);
			m_missile_rt[0] = { 0,0,0,0 };
			ME[0]->missile_start_x = 0;
			ME[0]->missile_start_y = 0;
			ME[0]->Set_Missile_X(0);
			ME[0]->Set_Missile_Y(0); // all 초기화
		}
	}

	for (int i = 1; i < 5; i++)
	{
		if (ME[i]->Get_Missile_Status() == TRUE)
		{
			if (0 >= m_missile_rt[i].left || 0 >= m_missile_rt[i].top || 920 <= m_missile_rt[i].right || 698 <= m_missile_rt[i].bottom)
			{
				missile_on[i] = FALSE;
				ME[i]->Set_Missile_Status(FALSE);
				m_missile_rt[i] = { 0,0,0,0 };
				ME[i]->missile_start_x = 0;
				ME[i]->missile_start_y = 0;
				ME[i]->Set_Missile_X(0);
				ME[i]->Set_Missile_Y(0); // all 초기화
			}
		}
	}
}

GameSystem::~GameSystem()
{

}