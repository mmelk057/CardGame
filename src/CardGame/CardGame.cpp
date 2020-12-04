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
	Chain<Green> a = Chain<Green>(cin, cf);
	Chain<Red> b = Chain<Red>(cin, cf);
	Green* green = new Green();
	Red* red = new Red();
	Card* cg = green;
	Card* cr = red;
	try {
		a += cg;
		a += cg;
		a += cg;
		a += cg;
		b += red;
		b += red;
	}
	catch(char* e){
		cout << e<<endl;
	}
	Players p1 = Players(string("TestName"));
	p1 += 4;
	try {
		p1.buyThirdChain();
		p1.buyThirdChain();
	}
	catch (char* e) {
		cout << e << endl;
	}
	cout << p1.getMaxNumChains()<<endl;
	cout<< p1.getNumChains()<<endl;
	p1.addChain(&a);
	p1.addChain(&b);
	cout << p1;
	return 0;
	Deck d = cf->getDeck();
	Hand h{};
	h += d.draw();
	h.saveState(1);
	return 1;
}
