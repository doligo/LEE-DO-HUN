#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Title_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pBack;
	JEngine::BitMap *m_pTitle;
	
	float m_p_title_x;
	float m_p_title_y;
	float m_p_speed_x;
public:
	Title_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	~Title_Scene();
};

