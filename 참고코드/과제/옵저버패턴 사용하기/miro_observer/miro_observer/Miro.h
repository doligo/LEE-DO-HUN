#include "Merco.h"
#pragma once

class Observer
{
public:
	virtual void Notify(string name) = 0;
};

class Subject
{
private:
	vector<Observer*> ob;
	string sb_name;
public:
	Subject(string name) : sb_name(name){}
	//감시할 옵저버 등록
	void AddPlayer(Observer* _ob)
	{
		ob.push_back(_ob);
	}
	void Notification()
	{
		vector<Observer*>::iterator seek = ob.begin();
		vector<Observer*>::iterator end = ob.end();

		while (seek != end)
		{
			(*seek)->Notify(sb_name);
			seek++;
		}
	}
protected:
	bool m_appear;
};

class Star : public Subject
{
public:
	Star() : Subject("★") { m_appear = false; }
	void Spawn()
	{
		m_appear = true;
		Notification();
	}
};

class Clover : public Subject
{
public:
	Clover() : Subject("♣") { m_appear = false; }
	void Spawn()
	{
		m_appear = true;
		Notification();
	}
};


class Miro : public Observer
{
private:
	Subject* m_sb;
	bool m_on_off; // 알림 받을지 말지
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

	void Notify(string name) override
	{
		if (m_on_off == true)
		{
			HIGH_GREEN
				cout << name.c_str() << endl;
			ORIGINAL
		}
	}

	void Set_Spawn(Subject* _m_sb, bool _m_on_off)
	{
		m_sb = _m_sb;
		m_on_off = _m_on_off;
		m_sb->AddPlayer(this);
	}

	void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	~Miro();
};

