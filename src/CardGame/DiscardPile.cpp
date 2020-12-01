#include "DiscardPile.h"
#include <fstream>
#include <cstdio>


const std::string DiscardPile::fileName = "DiscardPile.txt";

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

/*
Saves the save of a DiscardPile
*/
void DiscardPile::saveState() {
	std::ofstream outFile;
	outFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	for (Card* c : pile) {
		outFile << c->getFirst() << std::endl;
	}
	outFile.close();
}

/*
Recover previous DiscardPile state (if possible)
*/
DiscardPile DiscardPile::recoverState() {
	std::ifstream inFile;
	inFile.open(fileName, std::ifstream::in);
	if (!inFile) {
		//If the file cannot be opened, that implies that there is no previous
		//State to recover to - create a new DiscardPile
		return DiscardPile{};
	}
	inFile.close();
	DiscardPile p = DiscardPile{ inFile, CardFactory::getFactory() };
	//Remove previous state file
	std::remove(fileName.c_str());
	return p;
}







