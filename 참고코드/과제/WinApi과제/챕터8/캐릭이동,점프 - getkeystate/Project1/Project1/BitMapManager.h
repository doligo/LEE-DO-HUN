#include "BitMap.h"

#pragma once
class BitMapManager
{
private:
	static BitMapManager *m_pThis;
	BitMap *m_bt;
public:
	BitMapManager();

	static BitMapManager *GetInstance()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new BitMapManager;
		}
		return m_pThis;
	}

	void Init(HWND hWnd, HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y);
	void Release();

	~BitMapManager();
};

