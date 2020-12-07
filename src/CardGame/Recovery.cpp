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
			std::cout << currentChar;
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
	std::vector<std::string> rawChains{};
	std::string input;
	std::getline(is, input);
	const char* c_input = input.c_str();
	std::string workingStr;
	for (int i = 0; i < static_cast<int>(input.size()); i++) {
		if (c_input[i] == '\n') {
			break;
		}
		else if (c_input[i] == ' ') {
			rawChains.push_back(workingStr);
			workingStr = "";
		}
		else {
			workingStr += c_input[i];
		}
	}

	for (std::string rawInput : rawChains) {
		std::stringstream sstream;
		sstream << rawInput;
		
		char cardType = rawInput.empty() ? ' ' : rawInput.c_str()[0];
		
		//CREATE CHAIN
		if (dynamic_cast<Blue*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Blue>>(sstream, cf));
		}
		else if (dynamic_cast<Chili*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Chili>>(sstream, cf));
		}
		else if (dynamic_cast<Stink*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Stink>>(sstream, cf));
		}
		else if (dynamic_cast<Green*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Green>>(sstream, cf));
		}
		else if (dynamic_cast<Soy*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Soy>>(sstream, cf));
		}
		else if (dynamic_cast<Black*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Black>>(sstream, cf));
		}
		else if (dynamic_cast<Garden*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Garden>>(sstream, cf));
		} 
		else if(dynamic_cast<Red*>(cf->getCard(cardType)) != nullptr) {
			chains.push_back(std::make_shared<Chain<Red>>(sstream, cf));
		}
	}
}
