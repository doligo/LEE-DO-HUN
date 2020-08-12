#include <iostream>
#include <windows.h>
#include <string.h>
#pragma once
using namespace std;

#define PIECE_MAX 16
#define ALIVE 20
#define DEAD 21

struct Piece
{
	int x;
	int y;
	int draw;
	RECT rt;
	int first_move;
};

struct RECT_AND_STATUS
{
	RECT rt;
	int status;
	int player_num;
	int x;
	int y;
};

class chess_pieces
{
private:
	HDC MemDC[PIECE_MAX];
	HBITMAP hbtmap, old_hbtmap;
	BITMAP btmap;
public:
	chess_pieces();

	Piece m_King;
	Piece m_Queen;
	Piece m_Rook[2];
	Piece m_Bishop[2];
	Piece m_Knight[2];
	Piece m_Pawn[8];
	int m_x;
	int m_y;
	RECT_AND_STATUS m_All_Pawn[16];

	void Init_pieces(HDC hdc, int player_num);
	void Init_pieces_2(HDC hdc, int player_num);
	void Pieces_Draw(HDC hdc, int x, int y, string name);
	void Set_All_Pawn_Pos();

	~chess_pieces();
};

