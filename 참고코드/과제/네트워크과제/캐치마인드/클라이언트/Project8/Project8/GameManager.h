#pragma once
#include "BitMap_And_Draw.h"
#include "NetWork.h"
using namespace std;

class GameManager
{
private:
	static GameManager *SingleTone_GM;
	BitMap_And_Draw *Bt_Draw;
	NetWork *NT;

	int m_select_character;
public:
	GameManager();

	static GameManager *GetInstane()
	{
		if (SingleTone_GM == NULL)
			SingleTone_GM = new GameManager();
		return SingleTone_GM;
	}

	void Init(HWND hWnd);
	void Update();

	~GameManager();
};

