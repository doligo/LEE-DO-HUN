#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Game_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	float time;
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

