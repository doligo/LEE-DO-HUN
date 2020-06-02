#include "Block_Type.h"
#include <vector>
#pragma once

class Block_Factory
{
	vector<Block_Type*> bk_t;
	vector<Block*> bk;
	
public:
	~Block_Factory();

	virtual Block_Type* CreateBlockType() = 0;
	virtual Block* CreateBlock() = 0;

protected:
	void AddBlockType(Block_Type* _bk_t);
	void AddBlock(Block* _bk);
};

class Trigger_Block_Factory : public Block_Factory
{
public:
	virtual Block_Type* CreateBlockType();
	virtual Block* CreateBlock();
};

class Move_Block_Factory : public Block_Factory
{
public:
	virtual Block_Type* CreateBlockType();
	virtual Block* CreateBlock();
};

class Stopped_Block_Factory : public Block_Factory
{
public:
	virtual Block_Type* CreateBlockType();
	virtual Block* CreateBlock();
};

