#include <Windows.h>
#include <iostream>
#include <string>
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
	SIZE m_Charactersize[5];

public:
	BackGround();

	int player_x;
	int player_y;
	int menu_select;

	void Init_BackGround(HWND hWnd, HINSTANCE hInst);
	void Init_Player(HWND hWnd, HINSTANCE hInst);
	int Draw_TitleScreen(HDC hdc);
	void Draw_StageScreen(HDC hdc);
	void Draw_GameScreen(HDC hdc);
	void Draw_Character(HDC hdc);

	~BackGround();
};

