#include "TradeArea.h"

std::ostream & operator<<(std::ostream & os, const TradeArea& tradeArea) {
	bool flag = false;
	for (Card* const& i : tradeArea.cards) {
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

TradeArea& TradeArea::operator+= (Card* c) {
	cards.push_back(c);
	return *this;
}

bool TradeArea::legal(Card * c) const {
	bool flag = false;
	int first3 = 0;

	for (Card* const& i : cards) {
		if ( (c->getName()).compare(i->getName()) == 0 ) {
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

Card* TradeArea::trade(std::string s) {
	Card* flag = nullptr;
	std::list<Card*>::iterator iter = cards.begin();

	for (iter; iter != cards.end(); iter++) {
		if ( ((*iter)->getName()).compare(s) == 0 ) {
			flag = *iter;
			break;
		}
	}
	if (flag!=nullptr) {
		cards.erase(iter);
	}
	return flag;
}

int TradeArea::numCards() const {
	return static_cast<int>(cards.size());
}
std::vector<std::string> TradeArea::getUnique()
{
	std::list<Card*>::iterator ip;
	ip = std::unique(cards.begin(), cards.end());
	std::vector<std::string> unique;
	for (Card* const c : cards) {

	}
	return ();
}