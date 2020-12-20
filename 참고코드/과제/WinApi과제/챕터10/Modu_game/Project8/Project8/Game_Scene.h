#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

enum Paper_Color
{
	RED,
	GREEN,
	BLUE,
	YELLOW
};

#define UP 20
#define DOWN 21
#define LEFT 22
#define RIGHT 23

class Game_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::BitMap *m_pPaper[4];
	float time;

	int game_score;
	int paper_score;
	
	int game_time;
	int paper_x;
	int paper_y;
	int paper_dir;
	int visible_paper[2];
public:
	Game_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();

	virtual ~Game_Scene();
};

