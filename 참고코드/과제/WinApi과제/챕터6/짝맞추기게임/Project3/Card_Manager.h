#include "Card.h"
#pragma once

class Card_Manager : public Card
{
private:
protected:
public:
	Card_Manager();

	int Click(Card _card, int x, int y);
	
	~Card_Manager();
};

