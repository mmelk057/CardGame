#include "TradeArea.h"

TradeArea::TradeArea(istream & is , const CardFactory * cf)
{
	//TODO Construct Trade Area
}

TradeArea & TradeArea::operator+=(Card * c)
{
	cards.push_back(c);
	return *this;
}

bool TradeArea::legal(Card * c) const
{
	bool flag = false;
	int first3 = 0;

	for (Card* const& i : cards) {
		if (c->getName().compare(i->getName()) == 0) {
			flag = true;
			break;
		}
		first3++;
		if (first3 >= 3) {
			break;
		}
	}
	return flag;
}

Card * TradeArea::trade(string s)
{
	Card* flag = nullptr;
	list<Card*>::iterator iter = cards.begin();

	for (iter; iter != cards.end(); iter++) {
		if ((*iter)->getName().compare(s)==0) {
			flag = *iter;
			break;
		}
	}

	if (flag!=nullptr) {
		cards.erase(iter);
	}
	return flag;
}

int TradeArea::numCards() const
{
	return cards.size();
}

ostream & operator<<(ostream & os, TradeArea ta)
{
	bool flag = false;
	for (Card* const& i : ta.cards) {
		if (flag) {
			os << " ";
		}
		else {
			flag = true;
		}
		os << i->getName();
	}
	return os;
}
