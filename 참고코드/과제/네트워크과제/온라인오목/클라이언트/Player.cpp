#include "Player.h"

Player::Player()
{
	m_pStoneList = NULL;
	m_iStoneCount = 0;
	m_bMyWindState = false;
	m_iUndo = DEFAULT_UNDO;
	m_pStoneList_Enemy = NULL;
	m_iStoneCount_Enemy = 0;
}


bool Player::CompareStone(int player_check, int x, int y)
{
	if (player_check == 1)
	{
		for (int i = 0; i < m_iStoneCount; i++)
		{
			if (m_pStoneList[i].m_ix == x && m_pStoneList[i].m_iy == y)
				return true;
		}
	}

	else if (player_check == 2)
	{
		for (int i = 0; i < m_iStoneCount; i++)
		{
			if (m_pStoneList[i].m_ix == x && m_pStoneList[i].m_iy == y)
				return true;
		}

		for (int i = 0; i < m_iStoneCount_Enemy; i++)
		{
			if (m_pStoneList_Enemy[i].m_ix == x && m_pStoneList_Enemy[i].m_iy == y)
				return true;
		}
	}

	return false;
}

void Player::AllStoneDraw()
{

	for(int i = 0; i < m_iStoneCount; i++)
		m_DrawManager.DrawPoint(m_strStoneIcon, m_pStoneList[i].m_ix, m_pStoneList[i].m_iy);

	for (int i = 0; i < m_iStoneCount_Enemy; i++)
		m_DrawManager.DrawPoint(m_strStoneIcon_Enemy, m_pStoneList_Enemy[i].m_ix, m_pStoneList_Enemy[i].m_iy);
}

void Player::DrawStone(int x, int y)
{
	if(CompareStone(2, x, y))
		m_DrawManager.DrawPoint(m_strStoneIcon, x, y);
}

void Player::DrawStone_Enemy(int x, int y)
{
	if (CompareStone(2, x, y))
		m_DrawManager.DrawPoint(m_strStoneIcon_Enemy, x, y);
}


void Player::Undo(int Width, int Height)
{
	m_iStoneCount--;
	m_DrawManager.Erase(m_pStoneList[m_iStoneCount].m_ix, m_pStoneList[m_iStoneCount].m_iy, Width, Height);
}

void Player::CreateStone()
{
	if(CompareStone(2, m_Cursor.m_ix, m_Cursor.m_iy) == false)
	{
		m_pStoneList[m_iStoneCount].m_ix = m_Cursor.m_ix;
		m_pStoneList[m_iStoneCount++].m_iy = m_Cursor.m_iy;
		DrawStone(m_Cursor.m_ix, m_Cursor.m_iy);
	}
}

void Player::CreateStone_Enemy()
{
	if (CompareStone(2, m_Cursor_Enemy.m_ix, m_Cursor_Enemy.m_iy) == false)
	{
		m_pStoneList_Enemy[m_iStoneCount_Enemy].m_ix = m_Cursor_Enemy.m_ix;
		m_pStoneList_Enemy[m_iStoneCount_Enemy++].m_iy = m_Cursor_Enemy.m_iy;
		DrawStone_Enemy(m_Cursor_Enemy.m_ix, m_Cursor_Enemy.m_iy);
	}
}

void Player::Move(char ch, int Width, int Height)
{
	switch(ch)
	{
		case KEY_LEFT:
			if(m_Cursor.m_ix - 1 >= 0)
				m_Cursor.m_ix--;
			break;
		case KEY_RIGHT:
			if(m_Cursor.m_ix + 1 < Width)
				m_Cursor.m_ix++;
			break;
		case KEY_UP:
			if(m_Cursor.m_iy - 1 >= 0)
				m_Cursor.m_iy--;
			break;
		case KEY_DOWN:
			if(m_Cursor.m_iy + 1 < Height)
				m_Cursor.m_iy++;
			break;
	}
}


void Player::EraseCursor(int Width, int Height)
{
	m_DrawManager.Erase(m_Cursor.m_ix, m_Cursor.m_iy,Width,Height);
}

void Player::DrawCursor()
{
	m_DrawManager.DrawPoint(m_strCursorIcon, m_Cursor.m_ix, m_Cursor.m_iy);
}

void Player::DeleteStone()
{
	if(m_pStoneList != NULL)
	{
		delete[] m_pStoneList;
		m_pStoneList = NULL;
	}

	if (m_pStoneList_Enemy != NULL)
	{
		delete[] m_pStoneList_Enemy;
		m_pStoneList_Enemy = NULL;
	}
}

void Player::PlayerSet(int Width,int Height)
{
	DeleteStone();
	m_pStoneList = new Point[(Width*Height) / 2];
	m_iStoneCount = 0;
	m_Cursor.m_ix = Width * 0.5f;
	m_Cursor.m_iy = Height* 0.5f;
	m_bMyWindState = false;

	m_pStoneList_Enemy = new Point[(Width*Height) / 2];
}



int Player::NextStoneCheck(int x, int y, int addx, int addy,int Width, int Height)
{
	int count = 0;
	for(; (x >= 0 && x < Width) && (y >= 0 && y < Height); x += addx, y += addy)
	{
		if(CompareStone(1, x, y))
			count++;
		else
			break;
	}
	return count;
}

bool Player::WinCheck(int Width, int Height)
{
	int Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy, -1, 0, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy, 1, 0, Width, Height);
	if(Count + 1 == 5) //가로 검사
		return true;
	Count = 0;	
	Count += NextStoneCheck(m_Cursor.m_ix, m_Cursor.m_iy -1, 0, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix, m_Cursor.m_iy+1, 0, 1, Width, Height);
	if(Count + 1 == 5)//세로검사
		return true;
	Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy-1, -1, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy+1, 1, 1, Width, Height);
	if(Count + 1 == 5)//왼쪽대각선
		return true;
	Count = 0;
	Count += NextStoneCheck(m_Cursor.m_ix + 1, m_Cursor.m_iy-1, 1, -1, Width, Height);
	Count += NextStoneCheck(m_Cursor.m_ix - 1, m_Cursor.m_iy+1, -1, 1, Width, Height);
	if(Count + 1 == 5)//오른쪽대각선
		return true;

	return false;
}

void Player::SetCurosr_Enemy(int x, int y)
{
	m_Cursor_Enemy.m_ix = x;
	m_Cursor_Enemy.m_iy = y;
}

Player::~Player()
{
	if(m_pStoneList != NULL)
		delete[] m_pStoneList;

	if (m_pStoneList_Enemy != NULL)
		delete[] m_pStoneList_Enemy;
}
