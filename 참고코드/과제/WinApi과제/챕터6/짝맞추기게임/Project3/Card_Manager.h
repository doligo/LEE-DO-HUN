#include "Card.h"
#include<time.h>
#pragma once


class Card_Manager
{
private:
	static Card_Manager* m_pThis;
	Card* m_cd;
	int m_count;
protected:
public:
	Card_Manager();

	static Card_Manager* GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new Card_Manager;
		}
		return m_pThis;
	}

	void Init(HDC hdc, HINSTANCE hInst, int SpX = 1, int SpY = 1);
	void Draw(HDC hdc);
	void Click(int x, int y);
	
	~Card_Manager();
};

