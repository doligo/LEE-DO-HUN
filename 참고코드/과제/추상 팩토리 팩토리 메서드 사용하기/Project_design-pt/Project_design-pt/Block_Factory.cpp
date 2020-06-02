#include "Block_Factory.h"

Block_Factory::~Block_Factory()
{
	bk_t.clear();
	bk.clear();
}

void Block_Factory::AddBlockType(Block_Type* _bk_t)
{
	bk_t.push_back(_bk_t);
}

void Block_Factory::AddBlock(Block* _bk)
{
	bk.push_back(_bk);
}

Block_Type* Trigger_Block_Factory::CreateBlockType()
{
	return new Trigger_Block;
}

Block* Trigger_Block_Factory::CreateBlock()
{
	return new Entry_Potal;
}

Block_Type* Move_Block_Factory::CreateBlockType()
{
	return new Move_Block;
}

Block* Move_Block_Factory::CreateBlock()
{
	return new Character;
}

Block_Type* Stopped_Block_Factory::CreateBlockType()
{
	return new Stopped_Block;
}

Block* Stopped_Block_Factory::CreateBlock()
{
	return new Wall;
}


