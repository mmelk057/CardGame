#include "Cards.h"
#include "Chain.h"
#include "CardFactory.h"
#include <cctype>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <sstream>
#include <memory>


/*
* A General Process of Recovering Cards from a LIST
*/
void recoverCard(std::istream& is, const CardFactory* factory, std::list<Card*>& list) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck	
	if (is && !is.eof()) {
		char deckBuffer[105];
		is.getline(deckBuffer, 105);
		for (char currentChar : deckBuffer) {
			if (currentChar == '\n' || currentChar == '\0') {
				break;
			}
			Card* currentCard = factory->getCard(currentChar);
			if (currentCard == nullptr) {
				std::cout << std::endl << "INVALID Character ['" << currentChar << "']" << std::endl;
			}
			else {
				list.push_back(currentCard);
			}
		}
	}
}

/*
* A General Process of Recovering Cards from a VECTOR
*/
void recoverCard(std::istream& is, const CardFactory* factory, std::vector<Card*>& vector) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck	
	if (is && !is.eof()) {
		char deckBuffer[105];
		is.getline(deckBuffer, 105);
		for (char currentChar : deckBuffer) {
			if (currentChar == '\n' || currentChar == '\0') {
				break;
			}
			Card* currentCard = factory->getCard(currentChar);
			if (currentCard == nullptr) {
				std::cout << std::endl << "INVALID Character ['" << currentChar << "']" << std::endl;
			}
			else {
				vector.push_back(currentCard);
			}
		}
	}
}


/*
* A General Process of Recovering Cards from a QUEUE
*/
void recoverCard(std::istream& is, const CardFactory* factory, std::queue<Card*, std::list<Card*>>& queue) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck	
	if (is && !is.eof()) {
		char deckBuffer[105];
		is.getline(deckBuffer, 105);
		for (char currentChar : deckBuffer) {
			if (currentChar == '\n' || currentChar == '\0') {
				break;
			}
			Card* currentCard = factory->getCard(currentChar);
			if (currentCard == nullptr) {
				std::cout << std::endl << "INVALID Character ['" << currentChar << "']" << std::endl;
			}
			else {
				queue.push(currentCard);
			}
		}
	}
}

/*
* Recovers a list of chains.
* Stream is of the given format: "B4 S12 R3"
*/
void recoverChains(std::istream& is, const CardFactory* cf, std::vector<std::shared_ptr<ChainBase>>& chains) {
	char chainsBuffer[12];
	std::istream& tempStream = is.getline(chainsBuffer, 12);
	char currentChar;
	while (tempStream.get(currentChar)) {
		//DECODING FORMAT: [Type of Card][# of Chains of Type]  [Type of Card][# of Chains of Type] ...
		//ie. "B4 S12 R3"
		if (currentChar == '\n' || currentChar == '\0') {
			break;
		}
		if (cf->getCard(currentChar) != nullptr) {
			//ADD CARD TYPE TO STREAM
			std::stringstream chainStream;
			chainStream << currentChar;

			//ADD NUMBER OF CARDS OF A TYPE TO STREAM
			char currentNum;
			while (tempStream.get(currentNum)) {
				if (!std::isdigit(currentNum)) {
					break;
				}
				chainStream << currentNum;
			}

			//CREATE CHAIN
			if (dynamic_cast<Blue*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Blue>>(chainStream, cf));
			}
			else if (dynamic_cast<Chili*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Chili>>(chainStream, cf));
			}
			else if (dynamic_cast<Stink*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Stink>>(chainStream, cf));
			}
			else if (dynamic_cast<Green*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Green>>(chainStream, cf));
			}
			else if (dynamic_cast<Soy*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Soy>>(chainStream, cf));
			}
			else if (dynamic_cast<Black*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Black>>(chainStream, cf));
			}
			else if (dynamic_cast<Garden*>(cf->getCard(currentChar)) != nullptr) {
				chains.push_back(std::make_shared<Chain<Garden>>(chainStream, cf));
			}
			else {
				chains.push_back(std::make_shared<Chain<Red>>(chainStream, cf));
			}
		}
	}
}
