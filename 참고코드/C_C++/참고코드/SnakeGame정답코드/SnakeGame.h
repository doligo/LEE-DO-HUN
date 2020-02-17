#pragma once
#include"Block.h"
#include"MapDraw.h"
#include"Mecro.h"
#include"Snake.h"

#define CREATEFOODTIME 1000
enum GAMESTATE
{
	GAMESTATE_START = 1,
	GAMESTATE_EXIT
};

class SnakeGame
{
private:
	Snake* m_Snake;
	MapDraw DrawManager;
	Block* m_pMapBlock;
	Block* m_pObstacleGBlock;
	Block* m_pFoodBlock;
	Block* m_ptmp;
	Block* m_padd;
	int m_iMaxFoodCount;
	int m_iCurFoodCount;
	int m_iScore;
	int m_iCurClock;
	int m_iFoodClock;
	int m_iObstacleRatio;
	int m_iWidth;
	int m_iHeight;
	void WallRelease();
	void MapDraw();
	void TitleDraw();
	void GamePlay();
	void SetGame();
public:
	void Display();
	SnakeGame();
	~SnakeGame();
};

