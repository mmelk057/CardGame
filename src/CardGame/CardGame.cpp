// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include <iostream>
#include <map> 
#include <climits>
#include "CardGame.h"

int main()
{
	//Testing
	CardFactory* cf = CardFactory::getFactory();
	Chain<Green> a = Chain<Green>(cin, cf);
	Green* green = new Green();
	Card* c = green;
	try {
		for (int i = 0; i < 8; i++) {
			a += green;
			cout << a << endl;
			//cout<<a.sell()<<endl;
		}
	}
	catch(char* e){
		cout << e<<endl;
	}
	return 0;
	Deck d = cf->getDeck();
	Hand h{};
	h += d.draw();
	h.saveState(1);
	return 1;
}
