#include "SnakeGame.h"



SnakeGame::SnakeGame()
{
}

void SnakeGame::SetGame()
{
	m_iMaxFoodCount = 10;
	m_iCurFoodCount = 0;
	m_iScore = 0;
	m_iWidth = WIDTH;
	m_iHeight = HEIGHT;
	m_pMapBlock = NULL;
	m_iObstacleRatio = 40;
	m_pObstacleGBlock = NULL;
	m_pFoodBlock = NULL;
	for (int y = 0; y < m_iHeight; y++)
	{
		for (int x = 0; x < m_iWidth; x++)
		{
			if (y == 0 || y == m_iHeight - 1 || x == 0 || x == m_iWidth - 1)
				if (m_pMapBlock == NULL)
				{
					m_pMapBlock = new Block;
					m_pMapBlock->SetBlock(x, y, BLOCK_WALL, "▦");
				}
				else
				{
					m_ptmp = m_pMapBlock;
					while (m_ptmp->GetNextBlock() != NULL)
						m_ptmp = m_ptmp->GetNextBlock();
					m_padd = new Block;
					m_padd->SetBlock(x, y, BLOCK_WALL, "▦");
					m_ptmp->SetNextBlock(m_padd);
				}
		}
	}
}


void SnakeGame::MapDraw()
{
	system("cls");
	m_pMapBlock->LinkedDraw(m_pMapBlock);
	string str = "Score : ";
	str += to_string(m_iScore);
	DrawManager.DrawMidText(str, m_iWidth, m_iHeight+2);
}


void SnakeGame::TitleDraw()
{
	DrawManager.DrawMidText("★ ☆ ★ Snake Game ★ ☆ ★", m_iWidth, m_iHeight*0.2);
	DrawManager.DrawMidText("1.게임 시작", m_iWidth, m_iHeight*0.3);
	DrawManager.DrawMidText("2.게임 종료", m_iWidth, m_iHeight*0.4);
	DrawManager.DrawMidText("선택 : ", m_iWidth, m_iHeight *0.5);
}


void SnakeGame::GamePlay()
{

	m_Snake = new Snake;
	m_Snake->SetSnake(m_iWidth, m_iHeight);
	MapDraw();
	m_pObstacleGBlock->Relese(m_pObstacleGBlock);
	int count = (m_iHeight*m_iWidth) / m_iObstacleRatio;
	int x, y;
	for (int i = 0; i < count; i++)
	{
		x = (rand() % (m_iWidth - 2)) + 1;
		y = (rand() % (m_iHeight - 2)) + 1;
		if (m_pObstacleGBlock == NULL)
		{
			m_pObstacleGBlock = new Block;
			m_pObstacleGBlock->SetBlock(x, y, BLOCK_OBSTACLE, "▣");
		}
		else
		{
			m_ptmp = m_pObstacleGBlock;
			while (m_ptmp->GetNextBlock() != NULL)
				m_ptmp = m_ptmp->GetNextBlock();
			m_padd = new Block;
			m_padd->SetBlock(x, y, BLOCK_OBSTACLE, "▣");
			m_ptmp->SetNextBlock(m_padd);
		}
	}
	m_pObstacleGBlock->LinkedDraw(m_pObstacleGBlock);
	m_iFoodClock = clock();
	while (1)
	{
		m_iCurClock = clock();
		if (m_iCurFoodCount < m_iMaxFoodCount && m_iCurClock - m_iFoodClock > CREATEFOODTIME)
		{
			while (1)
			{
				x = (rand() % (m_iWidth - 2)) + 1;
				y = (rand() % (m_iHeight - 2)) + 1;
				if (!m_pObstacleGBlock->LenkedCollition(m_pObstacleGBlock, x, y))
					break;
			}
			if (m_pFoodBlock == NULL)
			{
				m_pFoodBlock = new Block;
				m_pFoodBlock->SetBlock(x, y, BLOCK_FOOD, "♡");
			}
			else
			{
				m_ptmp = m_pFoodBlock;
				while (m_ptmp->GetNextBlock() != NULL)
					m_ptmp = m_ptmp->GetNextBlock();
				m_padd = new Block;
				m_padd->SetBlock(x, y, BLOCK_FOOD, "♡");
				m_ptmp->SetNextBlock(m_padd);
			}
			m_iFoodClock = m_iCurClock;
			m_pFoodBlock->LinkedDraw(m_pFoodBlock);
			m_iCurFoodCount++;
		}
		m_Snake->Input();
		m_Snake->Move();
		if (m_pObstacleGBlock->LenkedCollition(m_pObstacleGBlock, m_Snake->GetHeadX(), m_Snake->GetHeadY()))
			break;
		if (m_pMapBlock->LenkedCollition(m_pMapBlock, m_Snake->GetHeadX(), m_Snake->GetHeadY()))
			break;
		if (m_Snake->GetHead()->LenkedCollition(m_Snake->GetHead()->GetNextBlock(), m_Snake->GetHeadX(), m_Snake->GetHeadY()))
			break;
		if (m_pFoodBlock->LenkedCollition(m_pFoodBlock, m_Snake->GetHeadX(), m_Snake->GetHeadY()))
		{
			m_Snake->CreateTail();
			m_iCurFoodCount--;
			m_iScore++;
			string str = "Score : ";
			str += to_string(m_iScore);
			DrawManager.DrawMidText(str, m_iWidth, m_iHeight + 2);
			m_Snake->SpeedUp();
		}
		m_Snake->Draw();
	}
	m_Snake->Release();
	delete m_Snake;
	m_iCurFoodCount = 0;
	m_Snake = NULL;
	m_pObstacleGBlock->LinkedErase(m_pObstacleGBlock);
	m_pObstacleGBlock->Relese(m_pObstacleGBlock);
	m_pObstacleGBlock = NULL;
	m_pFoodBlock->LinkedErase(m_pFoodBlock);
	m_pFoodBlock->Relese(m_pFoodBlock);
	m_pFoodBlock = NULL;
	m_iScore = 0;
	DrawManager.DrawMidText("★ ☆ ★ Game Over ★ ☆ ★", m_iWidth, m_iHeight*0.5);
	DrawManager.DrawMidText("Continue : Space Bar", m_iWidth, m_iHeight*0.6);
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == 32)
			break;
	}
}

void SnakeGame::Display()
{
	SetGame();
	int Select;
	while (1)
	{
		MapDraw();
		TitleDraw();
		cin >> Select;
		switch (Select)
		{
		case GAMESTATE_START:
			GamePlay();
			break;
		case GAMESTATE_EXIT:
			return;
		}
	}
}

void SnakeGame::WallRelease()
{
	m_pMapBlock->Relese(m_pMapBlock);
	m_pMapBlock = NULL;
}


SnakeGame::~SnakeGame()
{
	WallRelease();
}
