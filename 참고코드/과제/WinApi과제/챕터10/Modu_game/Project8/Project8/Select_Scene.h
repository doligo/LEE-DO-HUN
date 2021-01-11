#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Label.h"
#include <fstream>
#include <iostream>
#include <conio.h>

struct Show_Top_Rank
{
	int rank;
	int score;
};

class Select_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::Label *m_pShow_Rank[2];

	float time;
	Show_Top_Rank *rank[2];
public:
	Select_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();

	void Set_Show_Rank();
	bool OnClick_Game();
	bool OnClick_Game2();

	virtual ~Select_Scene();
};

