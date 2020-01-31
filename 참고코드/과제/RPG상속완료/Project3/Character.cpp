#include "Character.h"



Character::Character()
{
	m_iwidth = 30; // �׸��¿뵵�� define ����
	m_iheight = 30;
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
	cout << name->name << " ������!!";

	name->level += 1;

	stat = (rand() % 5);
	Draw_Gotoxy.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 4);
	cout << "���ݷ� " << stat << " ����!!";
	name->dmg += stat;

	stat = (rand() % 10);
	Draw_Gotoxy.gotoxy(m_iwidth * 0.53, m_iheight * 0.1 + 6);
	cout << "����� " << stat << " ����!!";
	name->total_hp += stat;
}

Character::~Character()
{
}
