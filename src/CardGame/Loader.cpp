#include <fstream>
#include <cstdio>
#include <vector>
#include "CardFactory.h"
#include "Loader.h"
#include "Deck.h"
#include "DiscardPile.h"


void recoverCards(std::istream& is, const CardFactory* factory, std::vector<Card*>& cardList);

/*
* On Init, the loader should fetch the previous state of the game
*/
Loader::Loader(std::string playerOneName, std::string playerTwoName) {
	CardFactory* cf = CardFactory::getFactory();
	//RECOVER STATE
	std::ifstream inFile;
	inFile.open(fileName, std::ifstream::in);
	if (!inFile) {
		//CREATE A NEW TABLE
	} else {
		//RECOVER TABLE
			
		//LOAD DECK
		Deck recoveredDeck = Deck(inFile, cf);
		//LOAD DISCARD PILE
		DiscardPile recoveredDP = DiscardPile(inFile, cf);
		//LOAD TRADE AREA
		//LOAD PLAYER #1
		//LOAD PLAYER #2
	}
	inFile.close();
	//REMOVE OLD STATE
	std::remove(fileName.c_str());
}

Loader::~Loader() {
	//SAVE STATE
}

/*
* Builds a new table object
*/
Table buildTable(std::string playerOneName, std::string playerTwoName) {
	return Table();
}

/*
* Recover Deck State
*/
Deck::Deck(std::istream& is, const CardFactory* factory) {
	recoverCards(is, factory, *this);
}

/*
* Recover DiscardPile State
*/
DiscardPile::DiscardPile(std::istream& is, const CardFactory* factory) {
	recoverCards(is, factory, this->pile);
}

/*
* A General Process of Recovering Cards
*/
void recoverCards(std::istream& is, const CardFactory* factory, std::vector<Card*>& cardList) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck
	if (!is.eof()) {
		char deckBuffer[104];
		is.getline(deckBuffer, 104);
		for (char currentChar : deckBuffer) {
			if (currentChar == '\n') {
				break;
			}
			Card* currentCard = factory->getCard(currentChar);
			if (currentCard == nullptr) {
				std::cout << std::endl << "INVALID Character ['" << currentChar << "']" << std::endl;
			}
			else {
				cardList.push_back(currentCard);
			}
		}
	}
}