#include "DiscardPile.h"


DiscardPile::DiscardPile(std::istream& is, const CardFactory* factory) {
	char character;
	while (is.get(character)) {
		if (character != '\n') {
			Card* card = factory->getCard(character);
			if (card == nullptr) {
				std::cout << "INVALID character provided ['" << character << "']" << std::endl;
			}
			else {
				this->pile.push_back(card);
			}
		}
	}
}

std::ostream& operator<< (std::ostream& os, const DiscardPile& pile) {
	pile.print(os);
	return os;
}

DiscardPile& DiscardPile::operator+= (Card* c) {
	pile.push_back(c);
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
	Card* currentFront = pile.front();
	pile.erase(pile.begin());
	return currentFront;
}

/*
Returns the top card from the DiscardPile
*/
Card* DiscardPile::top() const {
	return pile.front();
}







