#include "Map.h"

int main()
{
	Map m;

	m.Init_Map();
	while (1)
	{
		m.Map_Draw();
		m.Move();
	}


	return 0;
}
