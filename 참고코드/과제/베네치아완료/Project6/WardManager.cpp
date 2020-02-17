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
		name[i].item_word = NULL;
		name[i].on_screen = FALSE;
	}

	Load.open("Word.txt");
	if (!Load)
	{
		system("cls");
		cout << "해당 파일이 없습니다" << endl;
		_getch();
	}
	else
	{
		Load >> ward_max;
		while(!Load.eof())
		{
			Load >> name[j].name;
			j++; // 0 ~ 74까지 저장되고 마지막에 75가 됌
		}
	}
	Load.close();

}

void WardManager::Set_xy(_Ward *name)
{

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

void WardManager::Set_item(_Ward *name)
{
	for (int i = 0; i < WARD_MAX; i++)
	{
		name[i].item_word = (rand() % 25);
	}
}

int WardManager::Draw_Word(_Ward *name, int i)
{
	// 살아있는상태인 단어를 랜덤으로 출력


	i = (rand() % 75);

	if (name[i].status == TRUE)
	{
		name[i].on_screen = TRUE;

		if (name[i].item_word >= WORD_SPEED_UP && name[i].item_word <= SCREEN_CLEAR)
		{
			XY.gotoxy(name[i].x, name[i].y);
			SKY_BLUE
			cout << name[i].name;
		}
		else
		{
			XY.gotoxy(name[i].x, name[i].y);
			ORIGINAL
			cout << name[i].name;
		}
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
		num = name[i].name.length(); // 단어 길이 저장

		XY.gotoxy(name[i].x, name[i].y);
		XY.EraseWord(num);
		name[i].y++;
		if (name[i].y == HEIGHT - 1)
		{
			name[i].status = FALSE; // 단어 죽음
			name[i].on_screen = FALSE; // 스크린에서 사라짐
			return 1;
		}

		if (name[i].item_word >= WORD_SPEED_UP && name[i].item_word <= SCREEN_CLEAR)
		{
			XY.gotoxy(name[i].x, name[i].y);
			SKY_BLUE
			cout << name[i].name;
		}
		else
		{
			XY.gotoxy(name[i].x, name[i].y);
			ORIGINAL
			cout << name[i].name;
		}
	}
	return 0;
}

WardManager::~WardManager()
{

}