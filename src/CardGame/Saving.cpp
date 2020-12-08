#include "Cards.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>

void saveCardSet(std::ostream& os, std::vector<Card*>& cardVector) {
	for (Card* c : cardVector) {
		os << c->getFirst();
	}
	os << '\n';
}

void saveCardSet(std::ostream& os, std::list<Card*>& cardList) {
	for (Card* c : cardList) {
		os << c->getFirst();
	}
	os << '\n';
}

void saveCardSet(std::ostream& os, std::queue<Card*, std::list<Card*>> cardQueue) {
	std::vector<Card*> cards{};
	while (!cardQueue.empty()) {
		cards.push_back(cardQueue.front());
		cardQueue.pop();
	}
	for (Card* c : cards) {
		cardQueue.push(c);
	}
	for (Card* c : cards) {
		os << c->getFirst();
	}
	os << '\n';
}

