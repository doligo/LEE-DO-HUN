#include "Block_Type.h"

void Block_Type::SetBlock(Block* _block)
{
	block = _block;
}

Block* Block_Type::GetBlock()
{
	return block;
}

bool Trigger_Block::EquipCheck()
{
	Entry_Potal* entry_potal = dynamic_cast<Entry_Potal*>(GetBlock());
	Exit_Potal* exit_potal = dynamic_cast<Exit_Potal*>(GetBlock());
	Game_Clear_Potal* game_clear_potal = dynamic_cast<Game_Clear_Potal*>(GetBlock());

	if (entry_potal == NULL || exit_potal == NULL || game_clear_potal == NULL)
		return false;


	cout << "Ʈ���� ����� �ִ� ���Դϴ�" << endl;

	return entry_potal->Draw();

}


bool Move_Block::EquipCheck()
{
	Character* character = dynamic_cast<Character*>(GetBlock());


	if (character == NULL)
		return false;

	cout << "�����̴� ����� �ִ� ���Դϴ�" << endl;

	return character->Draw();

}

bool Stopped_Block::EquipCheck()
{
	Wall* wall = dynamic_cast<Wall*>(GetBlock());

	if (wall == NULL)
		return false;


	cout << "�ƹ��� ����� ���� ������ ���Դϴ�" << endl;

	return wall->Draw();

}