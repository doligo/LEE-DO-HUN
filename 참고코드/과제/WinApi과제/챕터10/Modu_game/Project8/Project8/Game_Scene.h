#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Label.h"

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

#define UP_END 148
#define DOWN_END 443
#define LEFT_END 16
#define RIGHT_END 290

class Game_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::BitMap *m_pPaper[4];
	JEngine::BitMap *m_pShow_Time; //남은시간
	JEngine::BitMap *m_pShow_Fever[3];
	JEngine::Label* m_pShow_Score;
	JEngine::Label* m_pShow_Paper_Score;

	float time;
	float game_time;
	float full_fever_time;
	int game_score;
	int paper_score;
	bool moving_check;
	
	int paper_x;
	int paper_y;
	int paper_dir;
	int visible_paper[2];

	int fever_lv;
	float fever_gauge;
	int fever_light;
	int combo_count;
public:
	Game_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();
	void Move();
	void Point();
	void Time();
	void Fever();

	virtual ~Game_Scene();
};

