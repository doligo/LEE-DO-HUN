#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include "Observer.h"

#define MAX_CHARACTER 7

#define TYPE_PLAYER 0
#define TYPE_MOB 1

struct Character_Info
{
	string name;
	int level;
	int dmg;
	int cur_hp;
	int total_hp;
	int cur_exp;
	int total_exp;
	int get_exp;
	int gold;
	int type; // 몹 or 플레이어

	string cr_weapon_type;// 착용 무기타입
	string cr_weapon_name;// 착용 무기이름
	int cr_weapon_dmg; // 착용 무기데미지
};

class Character : public Observer
{
private:
	MapDraw Draw_Gotoxy;
	int m_iwidth;
	int m_iheight;
public:
	int player_rsp; // 플레이어 가위바위보 상태
	int mob_rsp; // 몹 가위바위보 상태
	void Init_cr(Character_Info *name);
	void Level_up(Character_Info *name);

	virtual void Update();
	Character();
	~Character();
};

