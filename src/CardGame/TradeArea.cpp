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
	if (c != nullptr) {
		for (Card* const& i : cards) {
			if ((c->getName()).compare(i->getName()) == 0) {
				return true;
			}
		}
	}
	return false;
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
	if (flag != nullptr) {
		cards.erase(iter);
	}
	return flag;
}

int TradeArea::numCards() const {
	return static_cast<int>(cards.size());
}

bool comparePtrToCardTA(Card* a, Card* b) { 
	if (a != nullptr && b != nullptr) {
		return (*a < *b);
	}
	return false;
}

std::list<std::string> TradeArea::getUnique() {
	std::list<Card*> unique = cards;
	unique.sort(comparePtrToCardTA);
	unique.unique();
	std::list<std::string> uniqueStrings;
	for (Card* const c : unique) {
		uniqueStrings.push_back(c->getName());
	}
	return uniqueStrings;
}