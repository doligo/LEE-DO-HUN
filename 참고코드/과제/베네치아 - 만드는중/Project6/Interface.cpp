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

Interface::~Interface()
{

}