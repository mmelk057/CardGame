#include "Deck.h"


Deck::Deck(std::istream& is, const CardFactory* cf) {
	char character;
	while (is.get(character)) {
		if (character != '\n') {
			Card* currentCard = cf->getCard(character);
			if (currentCard == nullptr) {
				std::cout << std::endl << "INVALID Character ['" << character << "']" << std::endl;
			}
			else {
				this->push_back(currentCard);
			}
		}
	}
}


std::ostream& operator<< (std::ostream& os, const Deck& d) {
	d.display(os);
	return os;
}

void Deck::display(std::ostream& os) const {
	//Each card has an overload of the << operator to display the first
	//Letter of the card class
	for (Card* it: *(this)) {
		os << *(it);
	}
}

/*
Draw the top card from the deck
*/
Card* Deck::draw() {
	Card* front = back();
	pop_back();
	return front;
}

