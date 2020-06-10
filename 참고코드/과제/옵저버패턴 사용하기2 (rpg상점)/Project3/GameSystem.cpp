#include "GameSystem.h"

GameSystem::GameSystem()
{
	m_iwidth = WIDTH;
	m_iheight = HEIGHT;
	cr = NULL;
	m_ix = 0; // x의 시작지점
	m_iy = 0;
	total_mob = 0; // 총 몬스터숫자
	player_rsp = 0; // 가위바위보중 고른것
	mob_rsp = 0;
	m_iplay_over = FALSE;
	m_iselect_mob = 0; // 던전에서 몹선택
	m_iplayer_wdl = 0;
	m_imob_wdl = 0;
	wp = NULL;
	m_icritical = 0;
	m_icri_trigger = FALSE;
}

void GameSystem::First_Screen()
{
	int select = 0;

	while (1)
	{
		m_iplay_over = FALSE;

		BLUE
		Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight); // 파란테두리
		RED
		Draw_Ui.DrawMidText("☆★ 던전RPG ☆★", m_iwidth, m_iheight * 0.3);
		Draw_Ui.DrawMidText("New Game", m_iwidth, m_iheight * 0.4);
		Draw_Ui.DrawMidText("Load Game", m_iwidth, m_iheight * 0.5);
		Draw_Ui.DrawMidText("Game Exit", m_iwidth, m_iheight * 0.6);


		select = Draw_Ui.MenuSelectCursor(FIRST_MENU_COUNT, 3, m_iwidth * 0.38, m_iheight * 0.4);

		if (select == 1)
		{
			New_Game();
		}
		else if (select == 2)
		{
			Load_Game();
		}
		else
		{
			return;
		}
	}
}

void GameSystem::Second_Screen()
{

	int select = 0;

	while (m_iplay_over == FALSE)
	{
		system("cls");
		BLUE
		Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight); // 파란테두리
		RED
		Draw_Ui.DrawMidText("☆★ Menu ☆★", m_iwidth, m_iheight * 0.3);
		Draw_Ui.DrawMidText("Dongeon", m_iwidth, m_iheight * 0.37);
		Draw_Ui.DrawMidText("Player Info", m_iwidth, m_iheight * 0.44);
		Draw_Ui.DrawMidText("Monster Info", m_iwidth, m_iheight * 0.51);
		Draw_Ui.DrawMidText("Weapon Shop", m_iwidth, m_iheight * 0.58);
		Draw_Ui.DrawMidText("Save", m_iwidth, m_iheight * 0.65);
		Draw_Ui.DrawMidText("Exit", m_iwidth, m_iheight * 0.72);

		select = Draw_Ui.MenuSelectCursor(SECOND_MENU_COUNT, 2, m_iwidth * 0.34, m_iheight * 0.37);
		if (select == 1) // 던전
		{
			Dungeon_Enterance();
		}
		else if (select == 2) // 플레이어 정보
		{
			Show_Player_Info();
		}
		else if (select == 3) // 몹 정보
		{
			Show_Mob_Info();
		}
		else if (select == 4) // 무기 상점
		{
			Show_Shop(&cr[0]);
		}
		else if (select == 5) // 세이브
		{
			Save_Game();
		}
		else
		{
			return;
		}
	}

}

void GameSystem::Game_Screen()
{
	Init_cr(cr);
	Init_Weapon(); // protected 이기때문에 class 끼리 호환가능
	cr = new Character_Info[MAX_CHARACTER];
	First_Screen();
}

void GameSystem::New_Game()
{
	int i = 1;
	
	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	YELLOW
	Draw_Ui.DrawMidText("Player 이름 입력 : ", m_iwidth, m_iheight * 0.4);
	cin >> cr[0].name;
	ifstream load;
	load.open("DefaultPlayer.txt");
	while (!load.eof())
	{
		load >> cr[0].dmg;
		load >> cr[0].total_hp;
		load >> cr[0].total_exp;
		load >> cr[0].get_exp;
		load >> cr[0].level;
		load >> cr[0].gold;

		cr[0].cur_hp = cr[0].total_hp;
		cr[0].cur_exp = 0;
		cr[0].cr_weapon_dmg = 0;
		cr[0].type = TYPE_PLAYER;
	}
	load.close();

	load.open("DefaultMonster.txt");
	load >> total_mob; // 총 몹수 읽어오기
	while (!load.eof())
	{
		load >> cr[i].name;
		load >> cr[i].dmg;
		load >> cr[i].total_hp;
		load >> cr[i].total_exp;
		load >> cr[i].get_exp;
		load >> cr[i].level;
		load >> cr[i].gold;

		cr[i].cur_hp = cr[i].total_hp;
		cr[i].cur_exp = 0;
		cr[i].type = TYPE_MOB;

		i++; // 다음몹
	}
	load.close();


	Second_Screen();

}

void GameSystem::Load_Game()
{
	ifstream load;
	char buf[256] = {0};
	char file_buf[256] = {0};
	char OX = { 0 };
	int num = 0;
	int select = 0;
	int load_done = FALSE;

	while (load_done != TRUE)
	{
		system("cls");
		BLUE
			Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
		YELLOW
			for (int i = 1, j = 0; i <= 10; i++)
			{
				sprintf_s(file_buf, "SavePlayer%d.txt", i);
				load.open(file_buf);
				if (!load)
				{
					OX = 'X';
				}
				else
				{
					OX = 'O';
				}
				sprintf_s(buf, "%d번 슬롯 : <파일 여부 : %c>", i, OX);
				Draw_Ui.DrawMidText(buf, m_iwidth, m_iheight * 0.1 + j);
				j += 2;
				num = j;
				load.close();
			}

		Draw_Ui.DrawMidText("<-돌아가기                 ", m_iwidth, m_iheight * 0.1 + num);
		select = Draw_Ui.MenuSelectCursor(LOAD_MENU_COUNT, 2, m_iwidth * 0.2, m_iheight * 0.1);

		if (select <= 10)
		{
			int i = 1;
			sprintf_s(buf, "SavePlayer%d.txt", select);
			load.open(buf);
			if (!load)
			{
				system("cls");
				BLUE
				Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
				ORIGINAL
				Draw_Ui.DrawMidText("해당 파일이 없습니다", m_iwidth, m_iheight * 0.5);
				_getch();
			}
			else
			{
				while (!load.eof()) // player
				{
					load >> cr[0].name;
					load >> cr[0].dmg;
					load >> cr[0].total_hp;
					load >> cr[0].total_exp;
					load >> cr[0].cur_exp;
					load >> cr[0].level;
					load >> cr[0].gold;
					load >> cr[0].get_exp;
					load >> cr[0].cur_hp;

					load >> cr[0].cr_weapon_type;
					load >> cr[0].cr_weapon_name;
					load >> cr[0].cr_weapon_dmg;
				}
				load.close();

				if (cr[0].cr_weapon_type == "noting")
				{
					cr[0].cr_weapon_type = {0};
					cr[0].cr_weapon_name = {0};
					cr[0].cr_weapon_dmg = NULL;
				}

				sprintf_s(buf, "SaveMonster%d.txt", select);
				load.open(buf);
				load >> total_mob; // 총 몹수 읽어오기
				while (!load.eof()) // mob
				{
					load >> cr[i].name;
					load >> cr[i].dmg;
					load >> cr[i].total_hp;
					load >> cr[i].total_exp;
					load >> cr[i].get_exp;
					load >> cr[i].level;
					load >> cr[i].gold;

					cr[i].cur_hp = cr[i].total_hp;
					cr[i].cur_exp = 0;
					cr[i].type = TYPE_MOB;

					i++; // 다음몹
				}
				system("cls");
				BLUE
				Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
				ORIGINAL
				Draw_Ui.DrawMidText("Load 완료", m_iwidth, m_iheight * 0.5);
				load_done = TRUE;
				load.close();
				_getch();
			}
			
		}
		else
		{
			return;
		}
	}

	Second_Screen();
}

void GameSystem::Save_Game()
{
	ifstream load;
	ofstream save;
	char buf[256] = {0};
	char file_buf[256] = {0};
	char OX = { 0 };
	int num = 0;
	int select = 0;

	int save_done = FALSE;

	while (save_done != TRUE)
	{
		system("cls");
		BLUE
			Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
		YELLOW
			for (int i = 1, j = 0; i <= 10; i++)
			{
				sprintf_s(file_buf, "SavePlayer%d.txt", i);
				load.open(file_buf);
				if (!load)
				{
					OX = 'X';
				}
				else
				{
					OX = 'O';
				}
				sprintf_s(buf, "%d번 슬롯 : <파일 여부 : %c>", i, OX);
				Draw_Ui.DrawMidText(buf, m_iwidth, m_iheight * 0.1 + j);
				j += 2;
				num = j;
				load.close();
			}

		Draw_Ui.DrawMidText("<-돌아가기                 ", m_iwidth, m_iheight * 0.1 + num);
		select = Draw_Ui.MenuSelectCursor(LOAD_MENU_COUNT, 2, m_iwidth * 0.2, m_iheight * 0.1);

		if (select <= 10)
		{
			int i = 1;
			sprintf_s(buf, "SavePlayer%d.txt", select);
			save.open(buf);
			if (save.is_open()) // player
			{
				save << cr[0].name << " ";
				save << cr[0].dmg << " ";
				save << cr[0].total_hp << " ";
				save << cr[0].total_exp << " ";
				save << cr[0].cur_exp << " ";
				save << cr[0].level << " ";
				save << cr[0].gold << " ";
				save << cr[0].get_exp << " ";
				save << cr[0].cur_hp << endl;

				if (cr[0].cr_weapon_dmg != NULL)
				{
					save << cr[0].cr_weapon_type << " ";
					save << cr[0].cr_weapon_name << " ";
					save << cr[0].cr_weapon_dmg;
				}
				else
				{
					save << "noting";
				}
			}
			save.close();

			sprintf_s(buf, "SaveMonster%d.txt", select);
			save.open(buf);
			save << total_mob << endl; // 총 몹수 읽어오기
			if (save.is_open()) // mob
			{
				while (i < total_mob + 1)
				{
					save << cr[i].name << " ";
					save << cr[i].dmg << " ";
					save << cr[i].total_hp << " ";
					save << cr[i].total_exp << " ";
					save << cr[i].get_exp << " ";
					save << cr[i].level << " ";
					save << cr[i].gold << endl;

					i++; // 다음몹
				}

			}
			system("cls");
			BLUE
			Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
			ORIGINAL
			Draw_Ui.DrawMidText("Save 완료", m_iwidth, m_iheight * 0.5);
			save_done = TRUE;
			save.close();
			_getch();
		}
		else
		{
			return;
		}
	}

}

void GameSystem::Show_Player_Info()
{
	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	YELLOW
	Draw_Ui.gotoxy(m_iwidth * 0.7, m_iheight * 0.44);
	cout << "======" << cr[0].name << "<" << cr[0].level << "Lv>======" << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.50);
	cout << "공격력 = " << cr[0].dmg << "       생명력 = " << cr[0].cur_hp << "/" << cr[0].total_hp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.56);
	cout << "경험치 = " << cr[0].cur_exp << "/" << cr[0].total_exp << "    GetEXP = " << cr[0].get_exp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.58);
	cout << "Gold = " << cr[0].gold;
	if (cr[0].cr_weapon_dmg != NULL) // 무기소유시 출력
	{
		Draw_Ui.gotoxy(m_iwidth * 0.2, m_iheight * 0.60);
		cout << "무기타입 : " << cr[0].cr_weapon_type << " 무기이름 : " << cr[0].cr_weapon_name << " 공격력 : " << cr[0].cr_weapon_dmg;
	}

	_getch();
}

void GameSystem::Show_Mob_Info()
{
	float height = 0.12; // 세로값

	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	ORIGINAL
	for (int i = 1; i < MOB_MAX; i++)
	{
		Draw_Ui.gotoxy(m_iwidth * 0.6, m_iheight * height);
		cout << "======" << cr[i].name << "<" << cr[i].level << "Lv>======" << endl;
		height += ADD_HEIGHT;
		Draw_Ui.gotoxy(m_iwidth * 0.45, m_iheight * height);
		cout << "공격력 = " << cr[i].dmg << "      생명력 = " << cr[i].cur_hp << "/" << cr[i].total_hp << endl;
		height += ADD_HEIGHT;
		Draw_Ui.gotoxy(m_iwidth * 0.45, m_iheight * height);
		cout << "경험치 = " << cr[i].cur_exp << "/" << cr[i].total_exp << "    GetEXP = " << cr[i].get_exp << endl;
		height += ADD_HEIGHT;
		Draw_Ui.gotoxy(m_iwidth * 0.45, m_iheight * height);
		cout << "Gold = " << cr[i].gold << endl;
		height += ADD_HEIGHT;
	}

	_getch();
}

void GameSystem::Dungeon_Enterance()
{

	float height = 1; // 세로값
	char buf[256];
	int num = 1;
	int select = 0;

	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	SKY_BLUE
	Draw_Ui.gotoxy(m_iwidth * 0.68, m_iheight * 0.2);
	cout << "=====던전 입구=====" << endl;

	for (int i = 1; i < MOB_MAX; i++)
	{
		sprintf_s(buf, "%d층 던전 : [", num);
		Draw_Ui.DrawMidText(buf + cr[i].name + "]", m_iwidth, m_iheight * 0.3 + height);
		num += 1;
		height += 2;
	}
	Draw_Ui.DrawMidText("돌아가기", m_iwidth, m_iheight * 0.3 + height);

	select = Draw_Ui.MenuSelectCursor(DUNGEON_MENU_COUNT, 2, m_iwidth * 0.24, m_iheight * 0.35);

	if (select == 1)
	{
		m_iselect_mob = 1;
		Fight();
	}
	else if (select == 2)
	{
		m_iselect_mob = 2;
		Fight();
	}
	else if (select == 3)
	{
		m_iselect_mob = 3;
		Fight();
	}
	else if (select == 4)
	{
		m_iselect_mob = 4;
		Fight();
	}
	else if (select == 5)
	{
		m_iselect_mob = 5;
		Fight();
	}
	else if (select == 6)
	{
		m_iselect_mob = 6;
		Fight();
	}
	else
	{
		return;
	}

	_getch();
}

void GameSystem::Fight_Result(int mob_num)
{
	m_icritical = (rand() % 100) + 1;

	if (player_rsp == SCISSORS && mob_rsp == MOB_PAPER)
	{
	    if (cr[0].cr_weapon_dmg != NULL && m_icritical <= 30)
	    {
			m_icri_trigger = TRUE;
			cr[mob_num].cur_hp -= (cr[0].dmg + cr[0].cr_weapon_dmg) * 2;
	    }
		else if (cr[0].cr_weapon_dmg != NULL)
		{
			cr[mob_num].cur_hp -= cr[0].dmg + cr[0].cr_weapon_dmg;
		}
		else
		{
			cr[mob_num].cur_hp -= cr[0].dmg;
		}
		m_iplayer_wdl = WIN;
		m_imob_wdl = LOSE;
	}
	else if (player_rsp == SCISSORS && mob_rsp == MOB_ROCK)
	{
		cr[0].cur_hp -= cr[mob_num].dmg;
		m_iplayer_wdl = LOSE;
		m_imob_wdl = WIN;
	}
	else if (player_rsp == ROCK && mob_rsp == MOB_SCISSORS)
	{
		if (cr[0].cr_weapon_dmg != NULL && m_icritical <= 30)
		{
			m_icri_trigger = TRUE;
			cr[mob_num].cur_hp -= (cr[0].dmg + cr[0].cr_weapon_dmg) * 2;
		}
		else if (cr[0].cr_weapon_dmg != NULL)
		{
			cr[mob_num].cur_hp -= cr[0].dmg + cr[0].cr_weapon_dmg;
		}
		else
		{
			cr[mob_num].cur_hp -= cr[0].dmg;
		}
		m_iplayer_wdl = WIN;
		m_imob_wdl = LOSE;
	}
	else if (player_rsp == ROCK && mob_rsp == MOB_PAPER)
	{
		cr[0].cur_hp -= cr[mob_num].dmg;
		m_iplayer_wdl = LOSE;
		m_imob_wdl = WIN;
	}
	else if (player_rsp == PAPER && mob_rsp == MOB_ROCK)
	{
		if (cr[0].cr_weapon_dmg != NULL && m_icritical <= 30)
		{
			m_icri_trigger = TRUE;
			cr[mob_num].cur_hp -= (cr[0].dmg + cr[0].cr_weapon_dmg) * 2;
		}
		else if (cr[0].cr_weapon_dmg != NULL)
		{
			cr[mob_num].cur_hp -= cr[0].dmg + cr[0].cr_weapon_dmg;
		}
		else
		{
			cr[mob_num].cur_hp -= cr[0].dmg;
		}
		m_iplayer_wdl = WIN;
		m_imob_wdl = LOSE;
	}
	else if (player_rsp == PAPER && mob_rsp == MOB_SCISSORS)
	{
		cr[0].cur_hp -= cr[mob_num].dmg;
		m_iplayer_wdl = LOSE;
		m_imob_wdl = WIN;
	}
	else
	{
		m_iplayer_wdl = DRAW;
		m_imob_wdl = DRAW;
	}
}

void GameSystem::Fight_Info(int mob_num)
{

	//// 플레이어 정보
	YELLOW
	Draw_Ui.gotoxy(m_iwidth * 0.7, m_iheight * 0.1);
	cout << "======" << cr[0].name << "<" << cr[0].level << "Lv>======" << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 1);
	cout << "공격력 = " << cr[0].dmg << "       생명력 = " << cr[0].cur_hp << "/" << cr[0].total_hp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 2);
	cout << "경험치 = " << cr[0].cur_exp << "/" << cr[0].total_exp << "    GetEXP = " << cr[0].get_exp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 3);
	cout << "Gold = " << cr[0].gold;
	if (cr[0].cr_weapon_dmg != NULL) // 무기소유시 출력
	{
		Draw_Ui.gotoxy(m_iwidth * 0.2, m_iheight * 0.1 + 4);
		cout << "무기타입 : " << cr[0].cr_weapon_type << " 무기이름 : " << cr[0].cr_weapon_name << " 공격력 : " << cr[0].cr_weapon_dmg;
	}
	//// 가위 ,바위 보
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 6);
	cout << "가위 : 1   바위 : 2   보 : 3" << endl;

	if (player_rsp == SCISSORS) // 플레이어
		Draw_Ui.DrawMidText("가위", m_iwidth, m_iheight * 0.4);
	else if (player_rsp == ROCK)
		Draw_Ui.DrawMidText("바위", m_iwidth, m_iheight * 0.4);
	else if (player_rsp == PAPER)
		Draw_Ui.DrawMidText("보", m_iwidth, m_iheight * 0.4);


	RED // 승패무 출력
		if (m_iplayer_wdl == WIN && m_imob_wdl == LOSE)
		{
			Draw_Ui.DrawMidText("Win", m_iwidth, m_iheight * 0.4 + 1);
			Draw_Ui.DrawMidText("Lose", m_iwidth, m_iheight * 0.5 + 2);
		}
		else if (m_iplayer_wdl == LOSE && m_imob_wdl == WIN)
		{
			Draw_Ui.DrawMidText("Lose", m_iwidth, m_iheight * 0.4 + 1);
			Draw_Ui.DrawMidText("Win", m_iwidth, m_iheight * 0.5 + 2);
		}
		else if (m_iplayer_wdl == DRAW && m_imob_wdl == DRAW)
		{
			Draw_Ui.DrawMidText("Draw", m_iwidth, m_iheight * 0.4 + 1);
			Draw_Ui.DrawMidText("Draw", m_iwidth, m_iheight * 0.5 + 2);
		}


	if (m_icri_trigger == TRUE)
	{
		Draw_Ui.DrawMidText("크리티컬!!<데미지 2배>", m_iwidth, m_iheight * 0.4 + 2);
	}


	//// 몹 정보
	ORIGINAL
	Draw_Ui.gotoxy(m_iwidth * 0.64, m_iheight * 0.5 + 8);
	cout << "======" << cr[mob_num].name << "<" << cr[mob_num].level << "Lv>======" << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.5 + 9);
	cout << "공격력 = " << cr[mob_num].dmg << "       생명력 = " << cr[mob_num].cur_hp << "/" << cr[mob_num].total_hp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.5 + 10);
	cout << "경험치 = " << cr[mob_num].cur_exp << "/" << cr[mob_num].total_exp << "    GetEXP = " << cr[mob_num].get_exp << endl;
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.5 + 11);
	cout << "Gold = " << cr[mob_num].gold;

	ORIGINAL
	if (mob_rsp == 0 && player_rsp >= SCISSORS && player_rsp <= PAPER)
		Draw_Ui.DrawMidText("가위", m_iwidth, m_iheight * 0.5 + 3);
	else if (mob_rsp == 1 && player_rsp >= SCISSORS && player_rsp <= PAPER)
		Draw_Ui.DrawMidText("바위", m_iwidth, m_iheight * 0.5 + 3);
	else if (mob_rsp == 2 && player_rsp >= SCISSORS && player_rsp <= PAPER)
		Draw_Ui.DrawMidText("보", m_iwidth, m_iheight * 0.5 + 3);
}

void GameSystem::Player_Win(int mob_num)
{
	_getch();
	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	RED
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 2);
	cout << cr[0].name << " 승리!!";
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 4);
	cout << cr[0].name << "가 경험치 " << cr[mob_num].get_exp << "를 얻었습니다.";

	player_rsp = 0;
	mob_rsp = 0;
	m_iplayer_wdl = 0;
	m_imob_wdl = 0;
	cr[0].cur_exp += cr[mob_num].get_exp; // 플레이어가 경험치 획득
	cr[0].get_exp = cr[0].cur_exp; // get 경험치 변경
	cr[0].gold += cr[mob_num].gold; // 골드획득
	cr[mob_num].cur_hp = cr[mob_num].total_hp; // 패배한 상대 체력 초기화


	if (cr[0].cur_exp >= cr[0].total_exp)
	{
		_getch();
		Level_up(&cr[0]);
		cr[0].cur_hp = cr[0].total_hp; // 렙업시 체력회복
		cr[0].cur_exp = 0; //경험치 초기화
		cr[0].get_exp = 0; // 플레이어만 get_exp 초기화
		cr[0].total_exp += cr[0].total_exp * 0.2; // 총 필요경험치량 증가
	}

}
void GameSystem::Mob_Win(int mob_num)
{
	_getch();
	system("cls");
	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	RED
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 2);
	cout << cr[mob_num].name << " 승리!!";
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 4);
	cout << cr[mob_num].name << "가 경험치 " << cr[0].get_exp << "를 얻었습니다.";

	player_rsp = 0;
	mob_rsp = 0;
	m_iplayer_wdl = 0;
	m_imob_wdl = 0;
	cr[mob_num].cur_exp += cr[0].get_exp; // 몹이 경험치 획득
	cr[mob_num].gold += cr[0].gold; // 골드획득
	cr[0].cur_hp = cr[0].total_hp; // 패배한 상대 체력 초기화

	if (cr[mob_num].cur_exp >= cr[mob_num].total_exp)
	{
		_getch();
		Level_up(&cr[mob_num]);
		cr[mob_num].cur_hp = cr[mob_num].total_hp; // 렙업시 체력회복
		cr[mob_num].cur_exp = 0; //경험치 초기화
		cr[mob_num].total_exp += cr[mob_num].total_exp * 0.2; // 총 필요경험치량 증가
	}

	m_iplay_over = TRUE;

	_getch();
	ORIGINAL
	Draw_Ui.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 6);
	cout << "Game Over!!!!!!!!!!";
}


void GameSystem::Fight()
{
	int fight_over = FALSE;
	int i = 0;

	i = m_iselect_mob; // 몹 선택한것

	BLUE
	Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
	RED
	Draw_Ui.DrawMidText("------------------------ vs ------------------------", m_iwidth, m_iheight * 0.5);
	Fight_Info(i); // player, mob 정보

	while (fight_over == FALSE)
	{
		player_rsp = _getch(); // 가위바위보 선택
		mob_rsp = (rand() % 3); // 몹

		if (player_rsp == SCISSORS || player_rsp == ROCK || player_rsp == PAPER)
		{
			BLUE
			Draw_Ui.BoxDraw(m_ix, m_iy, m_iwidth, m_iheight);
			RED
			Draw_Ui.DrawMidText("------------------------ vs ------------------------", m_iwidth, m_iheight * 0.5);
			Fight_Result(i); // 가위바위보 계산후 출력
			Fight_Info(i); // player, mob 정보
		}

		m_icri_trigger = FALSE;

		if (cr[0].cur_hp <= 0)
		{
			Mob_Win(i);
			fight_over = TRUE;
		}
		else if (cr[i].cur_hp <= 0)
		{
			Player_Win(i);
			fight_over = TRUE;
		}
	}

}

GameSystem::~GameSystem()
{
	//// cr, wp 동적할당해제 된 코드를 지움
	//// 중복해제때문에 heap영역 오류생긴것
}