#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Select_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;

	float time;
public:
	Select_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	//bool ClickEvent();

	bool OnClick_Game();
	bool OnClick_Game2();

	virtual ~Select_Scene();
};

