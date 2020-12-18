#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Title_Scene : public JEngine::Scene
{
private:
	JEngine::BitMap *m_pTitle;
	
	float m_p_title_x;
	float m_p_title_y;
	float m_p_speed_x;

	std::function<bool()> clickEvent;
public:
	Title_Scene();

	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	bool OnClick_Select();

	virtual ~Title_Scene(); // 소멸자에 virtual 안써주면 메모리가 샌다
};

