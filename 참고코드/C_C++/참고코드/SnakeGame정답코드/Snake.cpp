#include "Snake.h"



Snake::Snake()
{
}


void Snake::SetSnake(int Width, int Height)
{
	m_bDrawState = false;
	m_bLiveState = true;
	m_iHeight = Height;
	m_iWidth = Width;
	m_iMoveSpeed = 250;
	m_eDeraction = DERECTION_NON;
	m_pHead = new Block;
	m_pHead->SetBlock(Width / 2, Height / 2, 0, 0, BLOCK_SNAKE_HEAD, "¢Á");
}


void Snake::CreateTail()
{
	Block* tmp = m_pHead;
	while (tmp->GetNextBlock() != NULL)
		tmp = tmp->GetNextBlock();
	Block* add = new Block;
	add->SetBlock(tmp->GetLastX(), tmp->GetLastY(), 0, 0, BLOCK_SNAKE_TAIL, "¡Û");
	tmp->SetNextBlock(add);
}

void Snake::MoveTail()
{
	Block* tmp = m_pHead;
	while (tmp->GetNextBlock() != NULL)
	{
		tmp->GetNextBlock()->SetPosition(tmp->GetLastX(), tmp->GetLastY());
		tmp = tmp->GetNextBlock();
	}
}
void Snake::Move()
{
	m_iCurClock = clock();
	if (m_bLiveState && m_iCurClock - m_iMoveClock >= m_iMoveSpeed)
	{
		m_pHead->LinkedErase(m_pHead);
		switch (m_eDeraction)
		{
		case DERECTION_NON:
			break;
		case DERECTION_LEFT:
				m_pHead->SetPosition(m_pHead->GetX() - 1, m_pHead->GetY());
			break;
		case DERECTION_RIGHT:
				m_pHead->SetPosition(m_pHead->GetX() + 1, m_pHead->GetY());
			break;
		case DERECTION_UP:
				m_pHead->SetPosition(m_pHead->GetX(), m_pHead->GetY() - 1);
			break;
		case DERECTION_DOWN:
				m_pHead->SetPosition(m_pHead->GetX(), m_pHead->GetY() + 1);
			break;
		}
		m_iMoveClock = m_iCurClock;
		m_bDrawState = true;
		MoveTail();
	}
}

void Snake::Draw()
{
	if (m_bDrawState)
	{
		m_pHead->LinkedDraw(m_pHead);
		m_bDrawState = false;
	}
}

void Snake::Input()
{
	char ch;
	if (kbhit())
	{
		ch = getch();
		switch (ch)
		{
		case LEFT:
			if (m_eDeraction != DERECTION_RIGHT)
				m_eDeraction = DERECTION_LEFT;
			break;
		case RIGHT:
			if (m_eDeraction != DERECTION_LEFT)
				m_eDeraction = DERECTION_RIGHT;
			break;
		case UP:
			if (m_eDeraction != DERECTION_DOWN)
				m_eDeraction = DERECTION_UP;
			break;
		case DOWN:
			if (m_eDeraction != DERECTION_UP)
				m_eDeraction = DERECTION_DOWN;
			break;
		default:
			break;
		}
	}
}

void Snake::Release()
{
	m_pHead->Relese(m_pHead);
}

Snake::~Snake()
{
}
