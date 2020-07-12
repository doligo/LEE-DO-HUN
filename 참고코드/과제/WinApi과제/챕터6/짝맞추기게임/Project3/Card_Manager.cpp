#include "Card_Manager.h"

Card_Manager::Card_Manager()
{

}

int Card_Manager::Click(Card _card, int x, int y)
{
	if (_card.rt.left <= x && _card.rt.right >= x && _card.rt.top <= y && _card.rt.bottom >= y)
	{
		return 1;
	}
	return 0;
}

Card_Manager::~Card_Manager()
{

}