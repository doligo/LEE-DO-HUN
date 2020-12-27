#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Game2_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::BitMap *m_pShow_Time;
	JEngine::BitMap *m_pShow_Fever[3];
	JEngine::BitMap *m_pFlight;
	float time;

	JEngine::RECT m_pFlight_Rt;
	JEngine::POINT m_pFlight_Pt;
	JEngine::RECT m_pMovable_Rt; // 움직일수있는 범위
public:
	Game2_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();

	virtual ~Game2_Scene();
};

