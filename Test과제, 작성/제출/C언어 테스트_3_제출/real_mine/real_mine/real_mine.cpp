#include "Mine_Game.h"

int main()
{
	srand((unsigned)time);

	Mine_Game mg;
	mg.Init();
	mg.Play();

	return 0;
}
