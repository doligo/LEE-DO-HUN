#include "Block.h"



Block::Block()
{
}

void Block::Draw()
{
	if (m_bBlockState)
		m_DrawManager.DrawPoint(m_strBlock, m_ix, m_iy);
}


void Block::SetBlock(int x, int y, int LastX, int LastY, BLOCK BlockState, string str)
{
	m_ix = x;
	m_iy = y;
	m_eBlock = BlockState;
	m_strBlock = str;
	m_pNextBlock = NULL;
	m_iLastX = LastX;
	m_iLastY = LastY;
}

void Block::LinkedDraw(Block* Node)
{
	while (Node != NULL)
	{
		Node->Draw();
		Node = Node->GetNextBlock();
	}
}

bool Block::LenkedCollition(Block* Node, int x, int y)
{
	while (Node != NULL)
	{
		if (Node->BlockCollition(x, y))
			return true;
		Node = Node->GetNextBlock();
	}
	return false;
}


void Block::LinkedErase(Block* Node)
{
	while (Node != NULL)
	{
		if(Node->GetLiveState())
			m_DrawManager.ErasePoint(Node->GetX(), Node->GetY());
		Node = Node->GetNextBlock();
	}
}

bool Block::BlockCollition(int x, int y)
{
	if (m_bBlockState && m_ix == x && m_iy == y)
	{
		if (m_eBlock == BLOCK_FOOD)
		{
			m_bBlockState = false;
			m_DrawManager.ErasePoint(m_ix, m_iy);
		}
		return true;
	}
	return false;
}


void Block::SetPosition(int x, int y)
{
	m_iLastX = m_ix;
	m_iLastY = m_iy;
	m_ix = x;
	m_iy = y;
}


void Block::Relese(Block* Node)
{
	if (Node == NULL)
		return;
	Relese(Node->GetNextBlock());
	delete Node;
}

void Block::SetBlock(int x, int y, BLOCK BlockState,string str)
{
	m_ix = x;
	m_iy = y;
	m_eBlock = BlockState;
	m_strBlock = str;
	m_pNextBlock = NULL;
}


Block::~Block()
{
}
