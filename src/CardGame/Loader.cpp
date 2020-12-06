#include <fstream>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <sstream>
#include <cctype>
#include "CardFactory.h"
#include "Cards.h"
#include "Loader.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Hand.h"
#include "Chain.h"

std::vector<ChainBase*> recoverChains(std::istream & is, const CardFactory * cf);
void recoverCard(std::istream&, const CardFactory*, std::list<Card*>&);
void recoverCard(std::istream&, const CardFactory*, std::vector<Card*>&);
void recoverCard(std::istream& is, const CardFactory* factory, std::queue<Card*, std::list<Card*>>& queue);


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


