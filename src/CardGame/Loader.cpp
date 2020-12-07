#include <fstream>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <sstream>
#include <cctype>
#include <memory>
#include "CardFactory.h"
#include "Cards.h"
#include "Loader.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Hand.h"
#include "Chain.h"

//##################################### RECOVERY ###########################################################
void recoverChains(std::istream &, const CardFactory *, std::vector<std::shared_ptr<ChainBase>>&);
void recoverCard(std::istream&, const CardFactory*, std::list<Card*>&);
void recoverCard(std::istream&, const CardFactory*, std::vector<Card*>&);
void recoverCard(std::istream& is, const CardFactory* factory, std::queue<Card*, std::list<Card*>>& queue);
//##########################################################################################################

//################################## LOADING START #########################################################

void Loader::saveState() {
	std::ofstream outFile;
	outFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	if (outFile) {
		//SAVE DECK
		Deck currDeck = table.getDeck();
		for (auto it = currDeck.begin(); it != currDeck.end(); it++) {
			outFile << (*it)->getFirst();
		}
		outFile << '\n';

		//SAVE DISCARD PILE
		DiscardPile currDP = table.getDiscardPile();
		for (Card* c : currDP.pile) {
			outFile << c->getFirst();
		}
		outFile << '\n';

		//SAVE TRADE AREA
		TradeArea currTA = table.getTradeArea();
		for (Card* c : currTA.cards) {
			outFile << c->getFirst();
		}
		outFile << '\n';

		//SAVE PLAYER ONE
		savePlayerState(outFile, table.getPlayerOne());
		
		//SAVE PLAYER TWO
		savePlayerState(outFile, table.getPlayerTwo());
	}
	else {
		std::cout << "Unable to save Table to {'" << fileName << "'}" << std::endl;
	}
	outFile.close();
}


void Loader::savePlayerState(std::ostream& os, const Player& player) {
	//SAVE NAME
	os << player.getName() << '\n';
	
	//SAVE COINS
	os << player.getNumCoins() << '\n';
	
	//SAVE CHAINS
	for (const std::shared_ptr<ChainBase> cb : player.chains) {
		const Card* cardType = cb->getReference();
		int chainSize = cb->getChainSize();
		os << cardType->getFirst() << chainSize << ' ';
	}
	os << '\n';

	//SAVE HAND
	for (Card* c : player.hand.queue._Get_container()) {
		os << c->getFirst();
	}
	os << '\n';
}


//######################################## RECOVERY START ##########################################################

void Loader::loadState() {
	loadState("", "");
}

/*
* Fetch the previous state of the game, IF it exists
*/
void Loader::loadState(std::string playerOneName, std::string playerTwoName) {
	CardFactory* cf = CardFactory::getFactory();
	//RECOVER STATE
	std::ifstream inFile{};
	inFile.open(fileName, std::ifstream::in);
	table = Table(inFile, cf);
	
	//If the deck is empty, generate a new deck with 104 cards!
	if (table.getDeck().empty()) {
		table.getDeck() = cf->getDeck();
	}

	if (!playerOneName.empty()) {
		table.getPlayerOne().name = playerOneName;
	}
	if (!playerTwoName.empty()) {
		table.getPlayerTwo().name = playerTwoName;
	}

	//If Player One's Hand is empty, Draw 5 cards
	if (table.getPlayerOne().hand.queue.empty()) {
		for (int i = 0; i < 5; i++) {
			table.getPlayerOne().hand += table.getDeck().draw();
		}
	}
	
	//If Player Two's Hand is empty, Draw 5 cards
	if (table.getPlayerTwo().hand.queue.empty()) {
		for (int i = 0; i < 5; i++) {
			table.getPlayerTwo().hand += table.getDeck().draw();
		}
	}

	inFile.close();
	//REMOVE OLD STATE
	std::remove(fileName.c_str());
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
	//LOAD NAME
	std::stringstream nameStream;
	std::string fetchedName;
	std::getline(is, fetchedName);
	nameStream << fetchedName;
	nameStream >> name;

	//LOAD COINS
	std::stringstream sstream;
	std::string fetchedCoins;
	std::getline(is, fetchedCoins);
	if (fetchedCoins.empty()) {
		coins = 0;
	}
	else {
		sstream << fetchedCoins;
		sstream >> coins;
	}

	//LOAD CHAINS
	recoverChains(is, cf, chains);

	//LOAD HAND
	hand = Hand(is, cf);
}

/*
* Load Hand State
*/
Hand::Hand(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, queue);
}

/*
* Load Deck State
*/
Deck::Deck(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, *this);
}

/*
* Load DiscardPile State
*/
DiscardPile::DiscardPile(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, this->pile);
}

/*
* Load TradeArea State
*/
TradeArea::TradeArea(std::istream& is, const CardFactory* factory) {
	recoverCard(is, factory, cards);
}


