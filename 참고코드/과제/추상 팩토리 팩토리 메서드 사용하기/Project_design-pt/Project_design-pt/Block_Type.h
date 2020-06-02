#include "Block.h"
#pragma once

class Block_Type
{
private:
	Block* block;

public:
	void SetBlock(Block* _block);
	virtual bool EquipCheck() = 0;

protected:
	Block* GetBlock();
};

class Trigger_Block : public Block_Type
{
public:
	virtual bool EquipCheck();
};

class Move_Block : public Block_Type
{
public:
	virtual bool EquipCheck();
};

class Stopped_Block : public Block_Type
{
public:
	virtual bool EquipCheck();
};

