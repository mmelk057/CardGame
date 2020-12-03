// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include "TradeArea.h"
#include <iostream>
#include <map> 
#include <climits>
#include "CardGame.h"

int main()
{
	//Testing
	CardFactory* cf = CardFactory::getFactory();
	TradeArea a = TradeArea(cin, cf);
	Green* green = new Green();
	Red* red = new Red();
	Card* cg = green;
	Card* cr = red;
	try {
		/*for (int i = 0; i < 6; i++) {
			a += cg;
			a += red;
		}*/
		a += cg;
		a += cg;
		a += red;
	}
	catch(char* e){
		cout << e<<endl;
	}
	cout << a;
	return 0;
	Deck d = cf->getDeck();
	Hand h{};
	h += d.draw();
	h.saveState(1);
	return 1;
}
