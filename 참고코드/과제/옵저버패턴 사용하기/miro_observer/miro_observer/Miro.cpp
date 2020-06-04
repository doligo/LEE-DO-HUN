#include "Miro.h"

Miro::Miro()
{

}

int Miro::Init()
{
	v.assign(HEIGHT, vector<int>(WIDTH, 0));

	for (vector<int>::size_type i = 0; i < v[0].size(); i++)
		v[0][i] = 1;
	v[1] = { 1, 2,	1,	0,	0,	0,	1,	0,	0,	0,	1,	21,	62,	0,	0,	0,	0,	64,	23,	1 };
	v[2] = { 1, 0,	1,	12,	1,	0,	0,	0,	1,	0,	1,	1,	1,	0,	0,	0,	0,	1,	1,	1 };
	v[3] = { 1, 0,	1,	1,	1,	1,	1,	1,	1,	31,	1,	0,	0,	0,	44,	42,	0,	0,	0,	1 };
	v[4] = { 1, 0, 0, 11, 1, 10, 0, 0, 33, 0, 1, 0, 0, 0, 40, 38, 0, 0, 0, 1 };
	v[5] = { 1, 0, 1, 1, 1, 0, 1, 61, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 };
	v[6] = { 1, 0, 0, 30, 1, 0, 1, 0, 1, 46, 1, 0, 0, 0, 0, 0, 0, 1, 25, 1 };
	v[7] = { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	v[8] = { 1, 0, 0, 0, 0, 0, 1, 14, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	v[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	v[10] = { 1, 19, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 47, 0, 0, 60, 0, 99 };
	v[11] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 45, 0, 34, 1, 1, 1, 1, 1, 1, 1, 1 };
	v[12] = { 1, 15, 0, 0, 0, 0, 0, 0, 1, 37, 1, 1, 1, 41, 0, 0, 63, 0, 54, 1 };
	v[13] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 24, 1, 1, 1, 1, 1, 1, 22, 1 };
	v[14] = { 1, 1, 1, 1, 1, 26, 50, 0, 66, 0, 1, 0, 1, 43, 1, 17, 0, 1, 1, 1 };
	v[15] = { 1, 0, 0, 51, 1, 1, 1, 1, 1, 55, 1, 56, 1, 0, 1, 1, 36, 1, 52, 1 };
	v[16] = { 1, 0, 0, 13, 1, 0, 0, 0, 1, 1, 1, 0, 65, 0, 1, 18, 0, 1, 0, 1 };
	v[17] = { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 1 };
	v[18] = { 1, 0, 0, 0, 0, 0, 1, 32, 1, 39, 0, 0, 0, 53, 0, 0, 20, 1, 16, 1 };
	for (vector<int>::size_type i = 0; i < v[19].size(); i++)
		v[19][i] = 1;

	return 0;
}

void Miro::Set_Block()
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 2;
	char buf[256];
	sprintf_s(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] <= ENTRY_MAX + ENTRY_START)
			{
				Entry_Potal[v[y][x] - ENTRY_START][X] = x;
				Entry_Potal[v[y][x] - ENTRY_START][Y] = y;
			}
			else if (v[y][x] >= EXIT_START && v[y][x] <= EXIT_MAX + EXIT_START)
			{
				Exit_Potal[v[y][x] - EXIT_START][X] = x;
				Exit_Potal[v[y][x] - EXIT_START][Y] = y;
			}
			else if (v[y][x] >= DOOR_START && v[y][x] <= DOOR_START + DOOR_MAX)
			{
				Door[v[y][x] - DOOR_START][X] = x;
				Door[v[y][x] - DOOR_START][Y] = y;
				Door[v[y][x] - DOOR_START][FLAG] = 1;
			}
			else if (v[y][x] >= SWITCH_START && v[y][x] <= SWITCH_START + SWITCH_MAX)
			{
				Switch[v[y][x] - SWITCH_START][Y] = y;
				Switch[v[y][x] - SWITCH_START][X] = x;
				Switch[v[y][x] - SWITCH_START][FLAG] = 1;
			}
			else if (v[y][x] == EXIT)
			{
				Exit[X] = x;
				Exit[Y] = y;
			}
		}
	}
}

int Miro::FindDoor(int x, int y)
{
	for (int i = 0; i < DOOR_MAX; i++)
	{
		if (Door[i][X] == x && Door[i][Y] == y && Door[i][FLAG])
			return i;
	}
	return -1;
}

int Miro::FindSwitch(int x, int y)
{
	for (int i = 0; i < SWITCH_MAX; i++)
	{
		if (Switch[i][X] == x && Switch[i][Y] == y && Switch[i][FLAG])
			return i;
	}
	return -1;
}

int Miro::FindEntryPotal(int x, int y)
{
	for (int i = 0; i < ENTRY_MAX; i++)
	{
		if (Entry_Potal[i][X] == x && Entry_Potal[i][Y] == y)
			return i;
	}
	return -1;
}

int Miro::FindExitPotal(int x, int y)
{
	for (int i = 0; i < EXIT_MAX; i++)
	{
		if (Exit_Potal[i][X] == x && Exit_Potal[i][Y] == y)
			return i;
	}
	return -1;
}

void Miro::MapDraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == WALL)
				printf("▩");
			else if (v[y][x] == CHARACTER)
			{
				RED
					printf("♠");
				ORIGINAL
			}
			else if (v[y][x] == EXIT)
				printf("☞");
			else if (FindEntryPotal(x, y) != -1)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (FindExitPotal(x, y) != -1)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (FindDoor(x, y) != -1)
			{
				GOLD
					printf("▒");
				ORIGINAL
			}
			else if (FindSwitch(x, y) != -1)
			{
				PUPPLE
					printf("⊙");
				ORIGINAL
			}
			else
				printf("  ");
		}
		printf("\n");
	}
	BLUE printf("입구 : ◎  ");
	YELLOW printf("출구 : ●\n");
	GOLD printf("문 : ▒  ");
	PUPPLE printf("스위치 : ⊙");
	ORIGINAL
}

void Miro::SwitchOnCheck()
{
	int index = FindSwitch(character[X], character[Y]);
	if (index != -1)
	{
		Switch[index][X] = -1;
		Switch[index][Y] = -1;
		Switch[index][FLAG] = 0;
		Door[index][X] = -1;
		Door[index][Y] = -1;
		Door[index][FLAG] = 0;
	}
}

void Miro::MoveCheck()
{
	int index = FindEntryPotal(character[X], character[Y]);
	if (index != -1)
	{
		character[X] = Exit_Potal[index][X];
		character[Y] = Exit_Potal[index][Y];
	}
}

void Miro::ExitCheck()
{
	if (v[character[Y]][character[X]] == EXIT)
		GameClear = 1;
}

void Miro::Move()
{
	char ch;
	ch = _getch();
	system("cls");
	v[character[Y]][character[X]] = NULL;
	switch (ch)
	{
	case LEFT:
		if (v[character[Y]][character[X] - 1] != WALL && FindDoor(character[X] - 1, character[Y]) == -1)
			character[X]--;
		break;
	case RIGHT:
		if (v[character[Y]][character[X] + 1] != WALL && FindDoor(character[X] + 1, character[Y]) == -1)
			character[X]++;
		break;
	case UP:
		if (v[character[Y] - 1][character[X]] != WALL && FindDoor(character[X], character[Y] - 1) == -1)
			character[Y]--;
		break;
	case DOWN:
		if (v[character[Y] + 1][character[X]] != WALL && FindDoor(character[X], character[Y] + 1) == -1)
			character[Y]++;
		break;
	}
	MoveCheck();
	SwitchOnCheck();
	ExitCheck();
	v[character[Y]][character[X]] = CHARACTER;
}

void Miro::InGame()
{
	Init();
	Set_Block();
	while (!GameClear)
	{
		MapDraw();
		Move();
	}
	system("cls");
	printf("탈출성공!!");
}

Miro::~Miro()
{

}