#pragma once
#include "MapDraw.h"

class Interface : public MapDraw
{
private:
public:
	Interface();

	void First_Screen();
	void Game_Screen();
	void Rank_Screen();
	~Interface();
};

