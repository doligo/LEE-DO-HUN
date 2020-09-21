#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#pragma once

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

	HDC GameDC[4]; ///////// 인게임 배경화면,플레이 등등
	HBITMAP m_GameBitMap[4];
	HBITMAP m_Old_GameBitMap[4];
	SIZE m_Gamesize[3];

	HDC CharacterDC[6]; ///////// 플레이어 캐릭터
	HBITMAP m_CharacterBitMap[6];
	HBITMAP m_Old_CharacterBitMap[6];
	SIZE m_Charactersize[6];

	HDC EnemyDC[11]; ///////// 장애물 (적)
	HBITMAP m_EnemyBitMap[11];
	HBITMAP m_Old_EnemyBitMap[11];
	SIZE m_Enemysize[11];

public:
	BackGround();

	int player_x;
	int player_y;
	int player_pose;
	int count_x;
	int count_x2;
	int jump_x;
	int jump_y;
	int degree;
	int jump_trigger;
	int menu_select;

	int back_ground_x;
	int back_ground_y;

	int enemy_x;
	int enemy_y;
	int enemy_change_count;
	int fire_ring_draw;

	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	void Init_Player(HWND hWnd, HINSTANCE hInst);
	void Init_Enemy(HWND hWnd, HINSTANCE hInst);
	int Draw_TitleScreen(HDC hdc);
	void Draw_StageScreen(HDC hdc);
	void Draw_GameScreen(HDC hdc);
	void Draw_Character(HDC hdc);
	void Draw_Enemy(HDC hdc);
	void Control_Character();

	~BackGround();
};

