#include "Mecro.h"
#pragma once

#define COUNT_MAX 9999

struct Ranking
{
	string name;
	int stage;
	int total_score;
};

class Rank
{
private:
	Ranking *count;
public:
	int Count_Rank();
	void Load_Rank(Ranking *name);
	Rank();
	~Rank();
};

