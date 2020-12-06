#ifndef PLAYERS_H
#define PLAYERS_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <string>
#include <vector>
#include "Chain.h"
#include "Hand.h"
#include "Cards.h"

class Player {
	public:
		Player(std::string&);
		Player(std::istream&, const CardFactory*);
		std::string getName() const;
		int getNumCoins() const;
		Player& operator+=(int);
		int getMaxNumChains() const;
		int getNumChains() const;
		ChainBase& operator[](int);
		void buyThirdChain();
		void printHand(std::ostream&, bool);
		friend std::ostream & operator<<(std::ostream &, const Player&);
		void addChain(ChainBase*);
		void addCard(Card*);
		~Player() = default;
	private:
		int coins;
		std::string name;
		std::vector<ChainBase*> chains;
		int chainLimit = 2;
		const int MAX_CHAINS = 3;
		Hand hand;
};

#endif