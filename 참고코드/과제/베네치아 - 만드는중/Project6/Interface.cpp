#include "Interface.h"


Interface::Interface()
{

}

void Interface::Life_Show(int num)
{
	// �ʵ�ο� ��Ʈ�׸��°� �߰�
	// ȭ�� ȸ���� ����
}

void Interface::First_Screen()
{
	system("cls");
	PLUM
	BoxDraw(0, 0, WIDTH, HEIGHT);
	BLUE
	DrawMidText("�� �� �� �� ġ �� �� ��", WIDTH, HEIGHT * 0.2);
	_getch();
}

Interface::~Interface()
{

}