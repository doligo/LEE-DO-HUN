#include "Interface.h"


Interface::Interface()
{

}

void Interface::First_Screen()
{
	system("cls");
	PLUM
	BoxDraw(0, 0, WIDTH, HEIGHT);
	BLUE
	DrawMidText("�� �� �� �� ġ �� �� ��", WIDTH, HEIGHT * 0.2);
}

void Interface::Game_Screen()
{
	system("cls");
	PLUM
	BoxDraw(0, 0, WIDTH, HEIGHT);
	BLUE
	LittleBox(WIDTH, HEIGHT * 0.7, WIDTH * 0.3, HEIGHT * 0.15); // �Է¹ڽ�
}

void Interface::Rank_Screen()
{
	system("cls");

	PLUM
	BoxDraw(0, 0, WIDTH, HEIGHT);
	LittleBox(WIDTH, HEIGHT * 0.1, WIDTH * 0.3, HEIGHT * 0.15); // �Է¹ڽ�
	ORIGINAL
	DrawMidText("�� ŷ", WIDTH, HEIGHT * 0.1 + 2);

	gotoxy(WIDTH * 0.1 - 4, HEIGHT * 0.1 + 5);
	for (int i = 0; i < WIDTH * 2 - 4; i++)
	{
		cout << "=";
	}
	ORIGINAL
	DrawMidText("Name                    Score                    Stage", WIDTH, HEIGHT * 0.1 + 7);
}

Interface::~Interface()
{

}