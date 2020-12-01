#include "Hand.h"
#include <fstream>
#include <cstdio>

const std::string Hand::fileName = "Hand.txt";

void Hand::display(std::ostream& os) const {
	for (auto it = queue._Get_container().begin(); it != queue._Get_container().end(); it++) {
		os << *(it) << ' ';
	}
}

std::ostream& operator<< (std::ostream& os, const Hand& hand) {
	hand.display(os);
	return os;
}

Hand::Hand(std::istream& is, const CardFactory* factory) {
	char character;
	while (is.get(character)) {
		if (character != '\n') {
			Card* curr = factory->getCard(character);
			if (curr == nullptr) {
				std::cout << "INVALID Character ['" << character << "']";
			}
			else {
				queue.push(curr);
			}
		}
	}
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
	Card* topCard = top();
	queue.pop();
	return topCard;
}

/*
Returns but does not remove the top card from the player's hand
*/
Card* Hand::top() {
	return queue.front();
}

/*
Saves the state of a given Hand instance
*/
void Hand::saveState(int identifier) {
	std::ofstream outFile;
	outFile.open(getFileName(identifier), std::ofstream::out | std::ofstream::trunc);
	for (Card* c : queue._Get_container()) {
		outFile << c->getFirst() << std::endl;
	}
	outFile.close();
}

/*
Recovers a given Hand instance
*/
Hand Hand::recoverState(int identifier) {
	std::ifstream inFile;
	inFile.open(getFileName(identifier), std::ifstream::in);
	if (!inFile) {
		//If file (previous state) does not exist, 
		//return a new Hand
		return Hand{};
	}
	inFile.close();
	Hand h = Hand{ inFile, CardFactory::getFactory() };
	//Remove previous state file
	std::remove(fileName.c_str());
	return h;
}
