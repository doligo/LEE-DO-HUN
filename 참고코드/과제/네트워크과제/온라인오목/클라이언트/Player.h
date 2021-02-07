#pragma once
#include"Mecro.h"
#include"MapDraw.h"

#define DEFAULT_UNDO 5

struct Point
{
	int m_ix;
	int m_iy;
};

class Player
{
private:
	MapDraw m_DrawManager;
	string m_strName;
	Point* m_pStoneList;
	Point m_Cursor;
	int m_iStoneCount;
	string m_strCursorIcon;
	string m_strStoneIcon;
	bool m_bMyWindState;
	int m_iUndo;
public:
	int NextStoneCheck(int x,int y,int addx,int addy, int Width, int Height);
	bool WinCheck(int Width,int Height);
	void DrawStone(int x, int y);
	void AllStoneDraw();
	bool CompareStone(int x, int y);
	void CreateStone();
	void Move(char ch,int Width,int Height);
	void DrawCursor();
	void EraseCursor(int Width, int Height);
	void PlayerSet(int Width, int Height);
	void DeleteStone();
	void Undo(int Width,int Height);
	inline void DownUndo() { m_iUndo--; }
	inline void SetUndo(int undo) { m_iUndo = undo; }
	inline int GetUndo(){ return m_iUndo; }
	inline Point GetCursor() { return m_Cursor; }
	inline string GetName() { return m_strName; }
	inline void SetStoneIcon(string Icon) { m_strStoneIcon = Icon; }
	inline void SetCursorIcon(string Icon) { m_strCursorIcon = Icon; }
	inline void SetName(string player_name){ m_strName = player_name; }
	Player();
	~Player();
};

