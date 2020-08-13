#include <iostream>
#include <windows.h>
#include <string.h>
#pragma once
using namespace std;

#define ALIVE 20
#define DEAD 21

struct RECT_AND_STATUS
{
	RECT rt;
	int status;
	int player_num;
	int x;
	int y;
};

static RECT_AND_STATUS m_All_Pawn[16];

class All_pieces_pos
{
private:
public:
	All_pieces_pos();

	void Set_All_Pawn_Pos();

	~All_pieces_pos();
};

