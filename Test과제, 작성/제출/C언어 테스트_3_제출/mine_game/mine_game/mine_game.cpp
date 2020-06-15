#include "Map.h"

int main()
{
	Map m;

	m.Init_Map();
	while (1)
	{
		m.Map_Draw_First();
		m.Move();
	}


	return 0;
}
