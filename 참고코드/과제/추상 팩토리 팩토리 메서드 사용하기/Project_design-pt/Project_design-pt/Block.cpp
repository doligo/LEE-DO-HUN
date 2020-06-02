#include "Block.h"

bool Character::Draw()
{
	cout << "¢¼" << endl;
	
	return true;
}

bool Wall::Draw()
{
	cout << "¢Ì" << endl;

	return true;
}

bool Entry_Potal::Draw()
{
	cout << "¡Ý" << endl;

	return true;
}

bool Exit_Potal::Draw()
{
	cout << "¡Ü" << endl;

	return true;
}

bool  Game_Clear_Potal::Draw()
{
	cout << "¢Ñ" << endl;

	return true;
}
