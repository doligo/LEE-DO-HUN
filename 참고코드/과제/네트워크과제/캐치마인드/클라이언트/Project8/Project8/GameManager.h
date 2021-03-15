#pragma once
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <iostream>
#include <string.h>
#include "BitMap_And_Draw.h"
using namespace std;

class GameManager
{
private:
	static GameManager *SingleTone_GM;
	BitMap_And_Draw *Bt_Draw;
public:
	GameManager();

	static GameManager *GetInstane()
	{
		if (SingleTone_GM == NULL)
			SingleTone_GM = new GameManager();
		return SingleTone_GM;
	}

	void Init(HWND hWnd);

	~GameManager();
};

