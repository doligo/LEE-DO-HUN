#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "TimeManager.h"

#define BULLET_MAX 15

enum dir {
	B_UP,
	B_DOWN,
	B_LEFT,
	B_RIGHT
};

struct Bullet_Info
{
	JEngine::RECT b_rt;
	int b_dir1;
	int b_dir2;
	int b_speed;
};

class Game2_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::BitMap *m_pShow_Time;
	JEngine::BitMap *m_pShow_Fever[3];
	JEngine::BitMap *m_pFlight;
	JEngine::BitMap *m_pBullet;
	JEngine::BitMap *m_pExplosion[3];

	bool player_alive;
	bool game_start;
	float game_start_time;
	float time;

	JEngine::RECT m_pFlight_Rt;
	JEngine::POINT m_pFlight_Pt;

	Bullet_Info *bullet[BULLET_MAX];
	int explosion_count;
public:
	Game2_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();

	void Set_Flight();
	void Set_Bullet();
	void Set_Bullet_Dir(int num, int start_point, int dir);
	void Out_of_Map();
	void Bullet_Collision();

	virtual ~Game2_Scene();
};

