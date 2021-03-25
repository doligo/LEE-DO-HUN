#pragma once
#include "BitMap_And_Draw.h"
#include "NetWork.h"
using namespace std;

#define CHARACTER_MAX 16

enum GAME_STATUS
{
	Status_Select_Character = 10,
	Status_Input_YourName,
	Status_Wait_Room,
	Status_Exit_Game
};

struct Charater_Pos
{
	int x;
	int y;
	RECT rt;
	int name;
};

class GameManager
{
private:
	static GameManager *SingleTone_GM;
	BitMap_And_Draw *Bt_Draw;
	NetWork *NT;

	Charater_Pos My_Character_Pos[CHARACTER_MAX];
	int m_select_character;
	int m_game_status;
	int m_my_mouse_x;
	int m_my_mouse_y;
	int m_Draw_Check_YN;
	int m_Draw_Check_WR;

	RECT m_enter_button;
	RECT m_exit_button;
	HWND m_NameBox;
	HWND m_ChatBox;
	HWND m_hWnd;
	HINSTANCE m_hInst;

	char m_Player_Name[512];
public:
	GameManager();

	static GameManager *GetInstane()
	{
		if (SingleTone_GM == NULL)
			SingleTone_GM = new GameManager();
		return SingleTone_GM;
	}

	void Init(HWND hWnd, HINSTANCE hInstance);
	void Update(LPARAM lParam, WPARAM wParam);
	void Input(LPARAM lParam , WPARAM wParam);
	void Set_Select_Character_Pos();

	~GameManager();
};

