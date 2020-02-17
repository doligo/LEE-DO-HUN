#pragma once
#include"MapDraw.h"
enum BLOCK
{
	BLOCK_SNAKE_HEAD,
	BLOCK_SNAKE_TAIL,
	BLOCK_WALL,
	BLOCK_FOOD,
	BLOCK_OBSTACLE
};
class Block
{
private:
	string m_strBlock;
	MapDraw m_DrawManager;
	BLOCK m_eBlock;
	bool m_bBlockState = true;
	int m_ix;
	int m_iy;
	int m_iLastX;
	int m_iLastY;
	Block* m_pNextBlock;
public:
	bool LenkedCollition(Block* Node,int x,int y);
	void SetPosition(int x, int y);
	void LinkedDraw(Block* Node);
	void LinkedErase(Block* Node);
	void Relese(Block* Node);
	void SetBlock(int x, int y, BLOCK BlockState,string str);
	void SetBlock(int x, int y,int LastX,int LastY, BLOCK BlockState, string str);
	void Draw();
	bool BlockCollition(int x, int y);
	inline bool GetLiveState()
	{
		return m_bBlockState;
	}
	inline int GetLastX()
	{
		return m_iLastX;
	}
	inline int GetLastY()
	{
		return m_iLastY;
	}
	inline int GetX()
	{
		return m_ix;
	}
	inline int GetY()
	{
		return m_iy;
	}
	inline void SetNextBlock(Block* add)
	{
		m_pNextBlock = add;
	}
	inline Block* GetNextBlock()
	{
		return m_pNextBlock;
	}
	Block();
	~Block();
};

