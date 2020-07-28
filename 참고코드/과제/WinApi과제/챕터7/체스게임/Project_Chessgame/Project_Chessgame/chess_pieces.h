#include <iostream>
#include <string.h>
#pragma once
using namespace std;

struct Piece
{
	int player_num;
	int x;
	int y;
};

class chess_pieces
{
private:
	Piece m_king;
	Piece m_Queen;
	Piece m_Rook[2];
	Piece m_Bishop[2];
	Piece m_Knight[2];
	Piece m_Pawn[8];
public:
	chess_pieces();

	void Init();

	~chess_pieces();
};

