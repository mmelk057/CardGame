#ifndef TABLE_H
#define TABLE_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER


#include <iostream>
#include <string>
#include "CardFactory.h"
#include "Player.h"
#include "TradeArea.h"
#include "DiscardPile.h"
#include "Deck.h"

class Table {
	private:
		DiscardPile discardPile{};
		TradeArea tradeArea{};
		Deck deck{};
		Player player1{};
		Player player2{};

	public:
		Table(std::istream&, const CardFactory*);
		Table(std::string, std::string, CardFactory*);
		bool win(std::string&) const;
		void printHand(bool) const;
		friend std::ostream & operator<<(std::ostream &, const Table&);

		Player& getPlayerOne() { return player1; }

		Player& getPlayerTwo() { return player2; }

		Deck& getDeck() { return deck; }

		TradeArea& getTradeArea() { return tradeArea; }

		DiscardPile& getDiscardPile() { return discardPile; }

		Table() = default;
		~Table() = default;
};

#endif