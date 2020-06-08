#include "Miro.h"

#define NOTICE_TIME1 3000
#define NOTICE_TIME2 6000

int main()
{
	int mytime1 = clock();
	int mytime2 = clock();

	Star* star = new Star();
	Clover *clover = new Clover();

    Miro* mi = new Miro;
	mi->Set_Spawn(star, true);
	mi->Set_Spawn(clover, true);

	////////////////
	mi->Init();
	mi->Set_Block();
	mi->MapDraw();
	while (!mi->GameClear)
	{
		if (clock() - mytime1 >= NOTICE_TIME1)
		{
			mi->gotoxy(2, 2);
			star->Spawn();
			mytime1 = clock();
			Sleep(1000);
			mi->MapDraw();
		}
		if (clock() - mytime2 >= NOTICE_TIME2)
		{
			mi->gotoxy(10, 2);
			clover->Spawn();
			mytime2 = clock();
			Sleep(1000);
			mi->MapDraw();
		}
	}

	delete star;
	delete clover;
	delete mi;

    return 0;
}
