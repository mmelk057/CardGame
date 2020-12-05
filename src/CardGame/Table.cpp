#include "Table.h"

Table::Table(istream & is, const CardFactory *cf)
{
	p1 = new Players(string("p1"));
	p2 = new Players(string("p2"));
	deck = Deck(is, cf);
	discardPile = DiscardPile();
	tradeArea = TradeArea(is,cf);
}

bool Table::win(std::string & winner)
{
	bool done = deck.size() == 0;
	if (done) {
		int p1Coins = p1->getNumCoins();
		int p2Coins = p2->getNumCoins();
		if (p1Coins > p2Coins) {
			winner = p1->getName();
		}
		else if (p2Coins > p1Coins) {
			winner = p2->getName();
		}
		else {
			winner = string("tie");
		}
	}
	return done;
}

void Table::printHand(bool wholeHand)
{
	cout << p1->getName()<<": ";
	p1->printHand(cout, wholeHand);
	cout << endl<< p1->getName() << ": ";
	p2->printHand(cout, wholeHand);
}

ostream & operator<<(ostream & os, Table t)
{
	os << t.p1 << endl;
	os << t.p2 << endl;
	os << t.discardPile << endl;
	os << t.tradeArea << endl;
	return os;
}
