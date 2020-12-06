#include "Table.h"

std::ostream& operator<<(std::ostream & os, const Table& table) {
	os << *(table.player1) << std::endl;
	os << *(table.player2) << std::endl;
	os << "Discard Pile: " << table.discardPile << std::endl;
	os << "Trade Area: " << table.tradeArea;
	return os;
}


Table::Table(std::istream& is, const CardFactory* cf) {
	//TODO 
}

Table::Table(std::string playerOneName, std::string playerTwoName, CardFactory* cf) {
	player1 = new Player(playerOneName);
	player2 = new Player(playerTwoName);
	deck = cf->getDeck();
	discardPile = DiscardPile();
	tradeArea = TradeArea();
	for (int i = 0; i < 5; i++) {
		player1->addCard(deck.draw());
		player2->addCard(deck.draw());
	}
}

bool Table::win(std::string& winner) const {
	bool done = deck.size() == 0;
	if (done) {
		int p1Coins = player1->getNumCoins();
		int p2Coins = player2->getNumCoins();
		if (p1Coins > p2Coins) {
			winner = player1->getName();
		}
		else if (p2Coins > p1Coins) {
			winner = player2->getName();
		}
		else {
			winner = std::string("tie");
		}
	}
	return done;
}

void Table::printHand(bool wholeHand) const {
	std::cout << player1->getName()<<": ";
	player1 -> printHand(std::cout, wholeHand);
	std::cout << std::endl<< player2->getName() << ": ";
	player2 -> printHand(std::cout, wholeHand);
}

