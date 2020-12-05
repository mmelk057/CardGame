#pragma once
#include "Cards.h"
#include "CardFactory.h"
#include <list>
using namespace std;
class TradeArea
{
public:
	TradeArea(istream&, const CardFactory*);
	TradeArea& operator+=(Card*);
	bool legal(Card*) const;
	Card* trade(string);
	int numCards() const;

	friend ostream & operator<<(ostream & os, TradeArea ta);
	
	TradeArea() = default;
	~TradeArea() = default;
private:
	list<Card*> cards;
};

