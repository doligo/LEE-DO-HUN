#pragma once
#include "Draw.h"

#define X 0
#define Y 1

#define WALL 50
#define MINE 51

#define ENTER 13

class Mine_Game : virtual public Draw
{
private:
	int **m_igame_map;
	int **m_igame_map2;
	int m_imypos[2]; // 내위치
	int m_imine_max; // 마인최대치
	int m_imine[7][2];
	int m_iempty_max;
	int m_width;
	int m_height;
	int m_ix;
	int m_iy;
public:
	Mine_Game();

	void Init();
	void Map_Init(int width, int height);
	int Control(int x = 1, int y = 1);
	string Symbol(int n);
	void Play();
	bool Check(int width, int height);
	void EmptyCheck(int width, int height, int x, int y);
	bool Win_Check(int width, int height);

	~Mine_Game();
};

