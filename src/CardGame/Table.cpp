#include "Table.h"

Table::Table(istream & is, const CardFactory *cf)
{
	
}

Table::Table(string p1Name, string p2Name, CardFactory *cf)
{
	p1 = new Players(p1Name);
	p2 = new Players(p2Name);
	deck = cf->getDeck();
	discardPile = DiscardPile();
	tradeArea = TradeArea();
	for (int i = 0; i < 5; i++) {
		p1->addCard(deck.draw());
		p2->addCard(deck.draw());
	}
}

bool Table::win(std::string & winner)const
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

void Table::printHand(bool wholeHand) const
{
	cout << p1->getName()<<": ";
	p1->printHand(cout, wholeHand);
	cout << endl<< p1->getName() << ": ";
	p2->printHand(cout, wholeHand);
}

ostream & operator<<(ostream & os, Table t)
{
	os << *t.p1 << endl;
	os << *t.p2 << endl;
	os << "Discard Pile: " << t.discardPile << endl;
	os << "Trade Area: " << t.tradeArea;
	return os;
}
