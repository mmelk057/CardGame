#include "DiscardPile.h"
#include <fstream>
#include <cstdio>

std::ostream& operator<< (std::ostream& os, const DiscardPile& pile) {
	if (pile.top() != nullptr) {
		os << *pile.top();
	}
	return os;
}

DiscardPile& DiscardPile::operator+= (Card* c) {
	if (c != nullptr) {
		pile.push_back(c);
	}
	return *(this);
}

void DiscardPile::print(std::ostream& os) const {
	for (Card* card : pile) {
		os << *(card) << ' ';
	}
}

/*
Returns and removes the top card from the DiscardPile
*/
Card* DiscardPile::pickUp() {
	if (pile.empty()) {
		return nullptr;
	}
	Card* currentFront = pile.back();
	pile.pop_back();
	return currentFront;
}

/*
Returns the top card from the DiscardPile
*/
Card* DiscardPile::top() const {
	if (pile.empty()) {
		return nullptr;
	}
	return pile.back();
}
