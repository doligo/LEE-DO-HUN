#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#pragma once

using namespace std;

#define END_MAP 6272

class BackGround
{
private:
	BITMAP B_Info;

	HDC MemDC[9]; ////////// 메인타이틀
	HBITMAP	m_BitMap[9];
	HBITMAP	m_Old_BitMap[9];
	SIZE m_size[8];

	HDC StageDC[2]; ///////// 스테이지표시
	HBITMAP	m_StageBitMap[2];
	HBITMAP	m_Old_StageBitMap[2];
	SIZE m_Stagesize;

	HDC GameDC[9]; ///////// 인게임 배경화면,플레이 등등
	HBITMAP m_GameBitMap[9];
	HBITMAP m_Old_GameBitMap[9];
	SIZE m_Gamesize[8];

	HDC CharacterDC[6]; ///////// 플레이어 캐릭터
	HBITMAP m_CharacterBitMap[6];
	HBITMAP m_Old_CharacterBitMap[6];
	SIZE m_Charactersize[6];

	HDC EnemyDC[11]; ///////// 장애물 (적)
	HBITMAP m_EnemyBitMap[11];
	HBITMAP m_Old_EnemyBitMap[11];
	SIZE m_Enemysize[11];

	RECT m_Enemy_rt[2]; //불링범위
	RECT m_Player_rt; // 플레이어범위
	RECT m_Money_rt[2]; // 돈주머니범위
	RECT m_Fire_rt; // 항아리불범위
	RECT m_Clear_rt; // 클리어범위

public:
	BackGround();

	int player_life;
	int player_score;
	int player_x;
	int player_y;
	int player_rt_y;
	int player_pose;
	int die_check;
	int count_x;
	int count_x2;
	int jump_x;
	int jump_y;
	int degree;
	int jump_trigger;
	int menu_select;
	int back_ground_x;
	int back_ground_y;
	int enemy_back_x[2];
	int enemy_back_y[2];
	int enemy_front_x[2];
	int enemy_front_y[2];
	int enemy_x_2;
	int enemy_y_2;
	int enemy_change_count;
	int enemy_change_count_2;
	int ring_draw;
	int front_draw;
	int first_ring_created;
	int second_ring_created;
	int first_front_created;
	int second_front_created;
	int money_x[2];
	int money_y[2];
	int select_money1;
	int select_money2;
	int save_x;
	int set_ring_trigger;
	int clear_check;
	int clear_performance_change_count;

	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	void Init_Player(HWND hWnd, HINSTANCE hInst);
	void Init_Enemy(HWND hWnd, HINSTANCE hInst);
	int Draw_TitleScreen(HDC hdc);
	void Draw_StageScreen(HDC hdc);
	void Draw_GameScreen(HDC hdc);
	void Draw_Character(HDC hdc);
	void Draw_Die_Character(HDC hdc);
	void Draw_Front_Ring(HDC hdc);
	void Draw_Back_Ring(HDC hdc);
	void Draw_Fire(HDC hdc);
	void Draw_Miter();
	void Control_Character();
	void Set_Ring();
	void Set_Enemy_Pos(int num);
	void Set_Front();
	void Set_Enemy_Pos2(int num);
	void Die_Check();
	void Die_And_Init();
	void Draw_Life();
	void Draw_Score();
	void MoneyEat_Check();
	void Clear_Check();
	void Draw_Clear_Dance(HDC hdc);
	void Draw_Clear_BackGround();

	~BackGround();
};

