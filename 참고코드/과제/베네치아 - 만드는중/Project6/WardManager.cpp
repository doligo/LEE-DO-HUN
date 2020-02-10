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
		name[i].x = (rand() % 64);
		name[i].y = 2;

		if (name[i].x >= 2 && name[i].x <= 63) // 0,1 ���� 65, 64 ����
		{
			i++;
		}
	}

}

void WardManager::Draw_Word(_Ward *name)
{
	// ����ִ»����� �ܾ �������� ���

	int i = 0;
	int old_time = 0;
	int cur_time = 0;

	old_time = clock();

	while (1)
	{
		cur_time = clock();

		if (cur_time - old_time >= 2000)
		{
			i = (rand() % 75);

			if (name[i].status == TRUE)
			{
				XY.gotoxy(name[i].x, name[i].y);
				cout << name[i].name;

				old_time = cur_time;
			}
		}

	}
	// ���� �ڵ�� play�� �ű��, �ϳ��� �ܾ� �����ϱ�
}

WardManager::~WardManager()
{

}