#include "Merco.h"
#pragma once

class Subject
{
	Miro mm;
};

class Observer
{

};

class Miro : public Observer
{
public:

	vector<vector<int>> v;
	int character[2];
	int Entry_Potal[ENTRY_MAX][2];
	int Exit_Potal[EXIT_MAX][2];
	int Exit[2];
	int Door[DOOR_MAX][3];
	int Switch[SWITCH_MAX][3];
	int GameClear = 0;

	Miro();

	int Init();
	void Set_Block();

	int FindDoor(int x, int y);
	int FindSwitch(int x, int y);
	int FindEntryPotal(int x, int y);
	int FindExitPotal(int x, int y);

	void MapDraw();
	void SwitchOnCheck();
	void MoveCheck();
	void ExitCheck();

	void Move();
	void InGame();

	~Miro();
};

