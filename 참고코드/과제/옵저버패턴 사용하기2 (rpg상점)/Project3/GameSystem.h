#pragma once
#include "Shop.h"

#define FIRST_MENU_COUNT 3 // 첫화면 메뉴 갯수
#define SECOND_MENU_COUNT 6 // 두번째화면 메뉴 갯수
#define DUNGEON_MENU_COUNT 7 // 던전메뉴 갯수
#define LOAD_MENU_COUNT 11
#define ADD_HEIGHT 0.033
#define MOB_MAX 7

#define ENTER 13
#define SCISSORS 49
#define ROCK 50
#define PAPER 51
#define MOB_SCISSORS 0
#define MOB_ROCK 1
#define MOB_PAPER 2

#define WIN 1
#define DRAW 2
#define LOSE 3


// 가상함수 상속시에 public 앞에 가상붙이고 소멸자에도 붙이기
class GameSystem : virtual public Shop
{
private:
	int m_ix; //시작 x축
	int m_iy; //시작 y축
	int m_iwidth;
	int m_iheight;
	MapDraw Draw_Ui;
	Character_Info *cr;
	int total_mob;
	int m_iplay_over;
	int m_iselect_mob;
	int m_iplayer_wdl; // 플레이어 win or draw or lose
	int m_imob_wdl;
	int m_icritical; // 2배 데미지 변수
	int m_icri_trigger;
public:
	void Game_Screen();
	void First_Screen();
	void New_Game();
	void Load_Game();
	void Save_Game();
	void Second_Screen();
	void Show_Player_Info();
	void Show_Mob_Info();
	void Dungeon_Enterance();
	void Fight();
	void Fight_Result(int mob_num);
	void Fight_Info(int mob_num);
	void Player_Win(int mob_num);
	void Mob_Win(int mob_num);
	GameSystem();
	~GameSystem();
};

