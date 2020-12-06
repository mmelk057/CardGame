#pragma once
#include "Players.h"
#include "TradeArea.h"
#include "DiscardPile.h"
#include "Deck.h"

class Table
{
public:
	Table(istream&, const CardFactory*);
	Table(string, string, CardFactory*);
	bool win(std::string&) const;
	void printHand(bool)const;
	friend ostream & operator<<(ostream &, Table);
	Table() = default;
	~Table() = default;
	Players* p1;
	Players* p2;
	Deck deck;
	DiscardPile discardPile;
	TradeArea tradeArea;
};

