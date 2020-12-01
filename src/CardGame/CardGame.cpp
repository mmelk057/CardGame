// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include "Hand.h"
#include <iostream>
#include <map> 
#include <climits>


int main()
{
	CardFactory* cf = CardFactory::getFactory();
	Deck d = cf->getDeck();
	Hand h{};
	h += d.draw();
	h.saveState(1);
	return 1;
}
