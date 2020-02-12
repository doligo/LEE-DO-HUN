#include "WardManager.h"

WardManager::WardManager()
{

}

void WardManager::Load_Ward(_Ward *name, int ward_max)
{
	ifstream Load;
	int j = 0;

	for (int i = 0; i < WARD_MAX; i++)
	{
		name[i].x = NULL;
		name[i].y = NULL;
		name[i].name = { "\0" };
		name[i].status = TRUE;
	}

	Load.open("Word.txt");
	if (!Load)
	{
		system("cls");
		cout << "�ش� ������ �����ϴ�" << endl;
		_getch();
	}
	else
	{
		Load >> ward_max;
		while(!Load.eof())
		{
			Load >> name[j].name;
			j++; // 0 ~ 74���� ����ǰ� �������� 75�� ��
		}
	}

}

void WardManager::Set_xy(_Ward *name)
{
	int check = FALSE;

	for (int i = 0; i < WARD_MAX;)
	{
		name[i].x = (rand() % 119);
		name[i].y = 1;

		if (name[i].x >= 2 && name[i].x <= 118)
		{
			i++;
		}
	}

}

int WardManager::Draw_Word(_Ward *name, int i)
{
	// ����ִ»����� �ܾ �������� ���


	i = (rand() % 75);

	if (name[i].status == TRUE)
	{
		XY.gotoxy(name[i].x, name[i].y);
		BLUE
		cout << name[i].name;
	}

	return i;

}

int WardManager::Drop_Word(_Ward *name, int i)
{
	int tmp_x = 0;
	int tmp_y = 0;
	int num = 0;
	

	if (name[i].status == TRUE)
	{
		num = name[i].name.length(); // �ܾ� ���� ����

		XY.gotoxy(name[i].x, name[i].y);
		XY.EraseWord(num);
		name[i].y++;
		if (name[i].y == HEIGHT - 1)
		{
			name[i].status = FALSE; // �ܾ� ����
			return 0;
		}
		XY.gotoxy(name[i].x, name[i].y);
		BLUE
		cout << name[i].name;
	}
	return 0;
}

WardManager::~WardManager()
{

}