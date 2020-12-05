// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include "TradeArea.h"
#include "Players.h"
#include <iostream>
#include <map> 
#include <climits>
#include "CardGame.h"

int main()
{
	//Testing
	CardFactory* cf = CardFactory::getFactory();
	Deck d = cf->getDeck();
	Hand h{};
	h += d.draw();
	h.saveState(1);
	return 1;
}
