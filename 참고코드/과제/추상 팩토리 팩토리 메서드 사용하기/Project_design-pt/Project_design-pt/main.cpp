#include "Block_Factory.h"

void DrawTest(Block_Type* _bk_t);

void main()
{
	Trigger_Block_Factory* tbf = new Trigger_Block_Factory();
	Move_Block_Factory* mbf = new Move_Block_Factory();
	Stopped_Block_Factory* sbf = new Stopped_Block_Factory();

	Block_Type* trigger_block = tbf->CreateBlockType();
	Block_Type* trigger_block2 = tbf->CreateBlockType();
	Block_Type* trigger_block3 = tbf->CreateBlockType();

	Block_Type* move_block = mbf->CreateBlockType();
	Block_Type* stopped_block = sbf->CreateBlockType();

	Block* entry_potal = tbf->CreateBlock();
	Block* exit_potal = tbf->CreateBlock2();
	Block* game_clear_potal = tbf->CreateBlock3();

	Block* character = mbf->CreateBlock();
	Block* wall = sbf->CreateBlock();

	trigger_block->SetBlock(entry_potal);
	trigger_block2->SetBlock(exit_potal);
	trigger_block3->SetBlock(game_clear_potal);

	move_block->SetBlock(character);

	stopped_block->SetBlock(wall);

	/////////////////////////////////////// 출력

	DrawTest(trigger_block);
	DrawTest(trigger_block2);
	DrawTest(trigger_block3);
	cout << endl;
	DrawTest(move_block);
	cout << endl;
	DrawTest(stopped_block);
	
	return;
}


void DrawTest(Block_Type* _bk_t)
{
	if (!_bk_t->EquipCheck())
		cout << "오류입니다" << endl;
}