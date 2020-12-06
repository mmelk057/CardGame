#include "Deck.h"

std::ostream& operator<< (std::ostream& os, const Deck& d) {
	d.display(os);
	return os;
}

void Deck::display(std::ostream& os) const {
	//Each card has an overload of the << operator to display the first
	//Letter of the card class
	for (Card* it: *(this)) {
		os << *(it) << ' ';
	}
}

/*
Draw the top card from the deck
*/
Card* Deck::draw() {
	Card* front = this->front();
	this->erase(begin());
	return front;
}

