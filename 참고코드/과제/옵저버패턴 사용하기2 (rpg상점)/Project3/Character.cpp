#include "Character.h"



Character::Character()
{
	m_iwidth = 30; // 그리는용도라 define 안함
	m_iheight = 30;
}

void Character::Update()
{
	cout << "**무기가 재입고 되었습니다**";
}

void Character::Init_cr(Character_Info *name)
{
	if (name != NULL)
	{
		delete[] name;
	}
}

void Character::Level_up(Character_Info *name)
{
	int stat = 0;

	system("cls");
	BLUE
	Draw_Gotoxy.BoxDraw(0, 0, m_iwidth, m_iheight);
	PUPPLE
	Draw_Gotoxy.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 2);
	cout << name->name << " 레벨업!!";

	name->level += 1;

	stat = (rand() % 5);
	Draw_Gotoxy.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 4);
	cout << "공격력 " << stat << " 증가!!";
	name->dmg += stat;

	stat = (rand() % 10);
	Draw_Gotoxy.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 6);
	cout << "생명력 " << stat << " 증가!!";
	name->total_hp += stat;
}

Character::~Character()
{
}
