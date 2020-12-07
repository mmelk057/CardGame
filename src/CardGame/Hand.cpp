#include "Hand.h"
#include <fstream>
#include <cstdio>


void Hand::display(std::ostream& os) const {
	for (auto it = queue._Get_container().begin(); it != queue._Get_container().end(); it++) {
		os << *(it) << ' ';
	}
}

std::ostream& operator<< (std::ostream& os, const Hand& hand) {
	hand.display(os);
	return os;
}

/*
Pushes a card to the back of the queue
*/
Hand& Hand::operator+= (Card* card) {
	queue.push(card);
	return *(this);
}


/*
Returns and removes a Card from a given index.
If the index is invalid, return a nullptr.
*/
Card* Hand::operator[] (int index) {
	if (index < 0 || index >= queue.size()) {
		return nullptr;
	}
	int i = 0;
	for (auto it = queue._Get_container().begin(); 
				it != queue._Get_container().end(); 
				it++, i++) {
		if (i == index) {
			Card* card = *(it);
			//We're simply removing the Card from the underlying container, not
			//deleting the Card object reference.
			static_cast<std::list<Card*>>(queue._Get_container()).erase(it);
			return card;
		}
	}
	return nullptr;
}

/*
Returns and removes the top card from the player's hand
*/
Card* Hand::play() {
	if (queue.empty()) {
		return nullptr;
	}
	Card* topCard = top();
	queue.pop();
	return topCard;
}

/*
Returns but does not remove the top card from the player's hand
*/
Card* Hand::top() const {
	if (queue.empty()) {
		return nullptr;
	}
	return queue.front();
}
