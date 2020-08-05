#include "chess_pieces.h"
#pragma once
class Player
{
private:
	chess_pieces *Cp;
public:
	Player();

	int m_player_num;
	void Init_Player(HDC hdc, int player_num);
	void Player_Pieces_Draw(HDC hdc);

	~Player();
};

