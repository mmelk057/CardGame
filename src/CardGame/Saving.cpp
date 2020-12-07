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
	for (Card* c : cardQueue._Get_container()) {
		os << c->getFirst();
	}
	os << '\n';
}

