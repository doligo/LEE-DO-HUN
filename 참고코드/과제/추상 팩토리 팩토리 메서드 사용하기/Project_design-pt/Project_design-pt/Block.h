#pragma once
#include <iostream>
using namespace std;

class Block
{
public:
	virtual bool Draw() = 0;
};

class Character : public Block
{
public:
	virtual bool Draw();
};

class Wall : public Block
{
public:
	virtual bool Draw();
};

class Entry_Potal : public Block
{
public:
	virtual bool Draw();
};

class Exit_Potal : public Block
{
public:
	virtual bool Draw();
};

class Game_Clear_Potal : public Block
{
public:
	virtual bool Draw();
};