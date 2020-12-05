#pragma once
#include "Players.h"
#include "TradeArea.h"
#include "DiscardPile.h"
#include "Deck.h"

class Table
{
public:
	Table(istream&, const CardFactory*);
	Table(string, string);
	bool win(std::string&);
	void printHand(bool);
	friend ostream & operator<<(ostream &, Table);
	~Table() = default;
private:
	Players* p1;
	Players* p2;
	Deck deck;
	DiscardPile discardPile;
	TradeArea tradeArea;
};

