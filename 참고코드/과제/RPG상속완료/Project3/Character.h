#pragma once
#include"Mecro.h"
#include"MapDraw.h"

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
	int type; // �� or �÷��̾�

	string cr_weapon_type;// ���� ����Ÿ��
	string cr_weapon_name;// ���� �����̸�
	int cr_weapon_dmg; // ���� ���ⵥ����
};

class Character
{
private:
	MapDraw Draw_Gotoxy;
	int m_iwidth;
	int m_iheight;
public:
	int player_rsp; // �÷��̾� ���������� ����
	int mob_rsp; // �� ���������� ����
	void Init_cr(Character_Info *name);
	void Level_up(Character_Info *name);
	Character();
	~Character();
};

