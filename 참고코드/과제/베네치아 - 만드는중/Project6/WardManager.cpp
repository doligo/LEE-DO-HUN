#include "WardManager.h"

WardManager::WardManager()
{

}

void WardManager::Load_Ward(_Ward *name, int ward_max)
{
	ifstream Load;
	int j = 0;

	if (name != NULL)
	{
		delete[] name;
	}
	name = new _Ward[WARD_MAX];

	for (int i = 0; i < WARD_MAX; i++)
	{
		name[i].x = NULL;
		name[i].y = NULL;
		name[i].name = { "\0" };
		name[i].status = 1;
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
	for (int i = 0; i < WARD_MAX; i++)
	{
		name[i].x = ((rand() >= 2) && (rand() <= 63)); // 0,1 ���� 65, 64 ����
		name[i].y = 2;
	}
}

WardManager::~WardManager()
{

}