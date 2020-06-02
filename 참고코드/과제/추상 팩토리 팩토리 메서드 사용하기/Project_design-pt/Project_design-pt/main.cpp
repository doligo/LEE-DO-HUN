#include "Block_Factory.h"

void DrawTest(Block_Type* _bk_t);

void main()
{
	Trigger_Block_Factory* tbf = new Trigger_Block_Factory();
	Move_Block_Factory* mbf = new Move_Block_Factory();
	Stopped_Block_Factory* sbf = new Stopped_Block_Factory();

	Block_Type* trigger_block = tbf->CreateBlockType();
	Block_Type* move_block = mbf->CreateBlockType();
	Block_Type* stopped_block = sbf->CreateBlockType();

	Block* entry_potal = tbf->CreateBlock();
	Block* character = mbf->CreateBlock();
	Block* wall = sbf->CreateBlock();

	trigger_block->SetBlock(entry_potal);
	move_block->SetBlock(character);
	stopped_block->SetBlock(wall);

	DrawTest(trigger_block);
	DrawTest(move_block);
	DrawTest(stopped_block);
	
	return;
}


void DrawTest(Block_Type* _bk_t)
{
	if (!_bk_t->EquipCheck())
		cout << "오류입니다" << endl;
}