#include "Mecro.h"
#include "Interface.h"
#include "WardManager.h"
#pragma once

#define FULL_HP 9
#define BACK_SPACE 8
#define ENTER 13
#define INSERT_WORD_MAX 19

class Play : virtual public WardManager
{
private:
	int m_iLife;
	int m_iScore;
	int m_iTotal_Score;
	int m_iStage;
	int m_iload_word;
	int m_inum;
	int m_iPause;
	int m_iSpeed;
	int m_iCreate_Speed;
	int m_iItem_Use;
	int m_iItem_Clear_Use;

	char m_iTmp_Iw[INSERT_WORD_MAX];
	string m_iName;
	string m_iWord;
	string m_iTmpWord;

	Interface Ui;
	_Ward *w;
public:
	Play();

	void Life_Name();
	void Start();
	void Game_Start();
	void Story();
	void Insert_Name();
	void Playing();
	int Draw_Drop();
	void Insert_Word();
	void Correct_Word();
	void Item_Word(int i);
	void Item_Clear_Screen();
	~Play();
};

