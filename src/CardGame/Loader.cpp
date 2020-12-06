#include <fstream>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <sstream>
#include <cctype>
#include "CardFactory.h"
#include "Loader.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Hand.h"
#include "Chain.h"

std::vector<ChainBase*> recoverChains(std::istream& is, const CardFactory* cf);
void recoverCard(std::istream&, const CardFactory*, std::list<Card*>&);
void recoverCard(std::istream&, const CardFactory*, std::vector<Card*>&);
void recoverCard(std::istream& is, const CardFactory* factory, std::queue<Card*, std::list<Card*>>& queue);

//template void recoverCard(std::istream& is, const CardFactory* factory, std::list<Card*> collection);

/*
* On Init, the loader should fetch the previous state of the game
*/
Loader::Loader(std::string playerOneName, std::string playerTwoName) {
	CardFactory* cf = CardFactory::getFactory();
	//RECOVER STATE
	std::ifstream inFile{};
	inFile.open(fileName, std::ifstream::in);
	table = Table(inFile, cf);
	inFile.close();
	//REMOVE OLD STATE
	std::remove(fileName.c_str());
}

Loader::~Loader() {
	//SAVE STATE
}

/*
* Recover Table State
*/
Table::Table(std::istream& is, const CardFactory* cf) {
	//TABLE IS A COMPOSITION OF DECK, DISCARD PILE, TRADE AREA, PLAYER #1 & PLAYER #2

	//LOAD DECK
	deck = Deck(is, cf);
	//LOAD DISCARD PILE
	discardPile = DiscardPile(is, cf);
	//LOAD TRADE AREA
	tradeArea = TradeArea(is, cf);
	//LOAD PLAYER #1
	player1 = Player(is, cf);
	//LOAD PLAYER #2
	player2 = Player(is, cf);
}

/*
* Recover Player State
*/
Player::Player(std::istream& is, const CardFactory* cf) {
	//RECOVER NAME
	std::stringstream nameStream;
	std::string fetchedName;
	std::getline(is, fetchedName);
	nameStream << fetchedName;
	nameStream >> name;

	//RECOVER COINS
	std::stringstream sstream;
	std::string fetchedCoins;
	std::getline(is, fetchedCoins);
	sstream << fetchedCoins;
	sstream >> coins;

	//RECOVER CHAIN BASES
	chains = recoverChains(is, cf);

	//RECOVER HAND
	hand = Hand(is, cf);
}

/*
* Recovers a list of chains.
* Stream is of the given format: "B4 S12 R3"
*/
std::vector<ChainBase*> recoverChains(std::istream& is, const CardFactory* cf) {
	std::vector<ChainBase*> chains{};
	char chainsBuffer[12];
	std::istream& tempStream = is.getline(chainsBuffer, 12);
	char currentChar;
	while (tempStream.get(currentChar)) {
		//DECODING FORMAT: [Type of Card][# of Chains of Type]  [Type of Card][# of Chains of Type] ...
		//ie. "B4 S12 R3"
		if (currentChar == '\n') {
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
			//ChainBase* newChain = nullptr;
			//if (dynamic_cast<Blue*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Blue*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Chili*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Chili*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Stink*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Stink*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Green*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Green*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Soy*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Soy*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Black*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Black*>(chainStream, cf);
			//}
			//else if (dynamic_cast<Garden*>(cf->getCard(currentChar)) != nullptr) {
			//	newChain = new Chain<Garden*>(chainStream, cf);
			//} else {
			//	newChain = new Chain<Red*>(chainStream, cf);
			//}

			//ADD IT TO LIST OF CHAINS
			//chains.push_back(newChain);
		}
	}
	return chains;
}

/*
* Recover a chain.
* Stream is of the given format: "B4", "S12", etc.
*/
template <typename T>
Chain<T>::Chain(std::istream& is, const CardFactory* cf) {
	//GET CARD TYPE
	char character;
	is.get(character);
	Card* card = cf->getCard(character);
	//T* card = dynamic_cast<T*>(cf->getCard(character));
	if (card == nullptr) {
		std::cout << "UNABLE TO RECOVER CHAIN - EMPTY CHAIN!";
	} else {
		//GET NUMBER OF CARDS
		std::stringstream numStream;
		char currentNum;
		while (is.get(currentNum)) {
			if (!std::isdigit(currentNum)) {
				break;
			}
			numStream << currentNum;
		}
		int numberOfCards;
		numStream >> numberOfCards;

		//INSERT CARDS
		for (int i = 0; i < numberOfCards; i++) {
			//cards.push_back(card);
		}
	}
};

/*
* Recover a Hand
*/
Hand::Hand(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, queue);
}

/*
* Recover Deck State
*/
Deck::Deck(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, *this);
}

/*
* Recover DiscardPile State
*/
DiscardPile::DiscardPile(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, this->pile);
}

/*
* Recover TradeArea State
*/
TradeArea::TradeArea(std::istream& is, const CardFactory* cf) {
	recoverCard(is, cf, cards);
}

/*
* A General Process of Recovering Cards from a LIST
*/
void recoverCard(std::istream& is, const CardFactory* factory, std::list<Card*>& list) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck	
	if(is && !is.eof()) {
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
				vector.push_back(currentCard);
			}
		}
	}
}


/*
* A General Process of Recovering Cards from a QUEUE
*/
void recoverCard(std::istream& is, const CardFactory* factory, std::queue<Card*,std::list<Card*>>& queue) {
	//STRATEGY: GET AN ARBITRARY LINE, THEN PROCEED TO PARSE
	//There is a MAXIMUM of 104 cards in a deck	
	if (is && !is.eof()) {
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
				queue.push(currentCard);
			}
		}
	}
}