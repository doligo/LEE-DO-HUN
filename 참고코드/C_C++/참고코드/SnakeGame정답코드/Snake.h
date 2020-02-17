#pragma once
#include"Block.h"
enum DERECTION
{
	DERECTION_NON,
	DERECTION_LEFT,
	DERECTION_RIGHT,
	DERECTION_UP,
	DERECTION_DOWN
};
#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

class Snake
{
private:
	bool m_bLiveState = false;
	bool m_bDrawState = true;
	DERECTION m_eDeraction = DERECTION_NON;
	Block* m_pHead;
	int m_iCurClock;
	int m_iMoveClock;
	int m_iMoveSpeed = 250;
	int m_iWidth;
	int m_iHeight;
public:
	void SetSnake(int Width,int Height);
	void CreateTail();
	void Draw();	
	inline void SpeedUp()
	{
		if(m_iMoveSpeed > 50)
			m_iMoveSpeed -= 10;
	}
	inline Block* GetHead()
	{
		return m_pHead;
	}
	inline int GetHeadX()
	{
		return m_pHead->GetX();
	}
	inline int GetHeadY()
	{
		return m_pHead->GetY();
	}
	void Input();
	void MoveTail();
	void Move();
	void Release();
	Snake();
	~Snake();
};

