#include "DiscardPile.h"
#include <fstream>
#include <cstdio>

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
	if (pile.empty()) {
		return nullptr;
	}
	Card* currentFront = pile.front();
	pile.erase(pile.begin());
	return currentFront;
}

/*
Returns the top card from the DiscardPile
*/
Card* DiscardPile::top() const {
	if (pile.empty()) {
		return nullptr;
	}
	return pile.front();
}

/*
Saves the save of a DiscardPile
*/
//void DiscardPile::saveState() {
//	std::ofstream outFile;
//	outFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
//	for (Card* c : pile) {
//		outFile << c->getFirst() << std::endl;
//	}
//	outFile.close();
//}

/*
Recover previous DiscardPile state (if possible)
*/
//DiscardPile DiscardPile::recoverState() {
//	std::ifstream inFile;
//	inFile.open(fileName, std::ifstream::in);
//	if (!inFile) {
		//If the file cannot be opened, that implies that there is no previous
		//State to recover to - create a new DiscardPile
//		return DiscardPile{};
//	}
//	inFile.close();
//	DiscardPile p = DiscardPile{ inFile, CardFactory::getFactory() };
	//Remove previous state file
//	std::remove(fileName.c_str());
//	return p;
//}