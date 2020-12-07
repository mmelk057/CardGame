#ifndef PLAYER_H
#define PLAYER_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <string>
#include <vector>
#include "Chain.h"
#include "Hand.h"
#include "Cards.h"

class Loader;

class Player {
	friend class Loader;
	public:
		std::string getName() const;
		int getNumCoins() const;
		int getMaxNumChains() const;
		int getNumChains() const;
		void buyThirdChain();
		void printHand(std::ostream&, bool) const;
		friend std::ostream & operator<<(std::ostream&, const Player&);
		void addChain(ChainBase*);
		void addCard(Card*);

		//Operator overloads
		Player& operator+=(int);
		ChainBase& operator[](int);

		//Constructor(s) & Destructor
		Player(std::string&);
		Player(std::istream&, const CardFactory*);
		Player() = default;
		~Player() = default;

	private:
		std::string name;
		int coins = 0;
		std::vector<ChainBase*> chains{};
		int chainLimit = 2;
		static const int MAX_CHAINS;
		Hand hand{};
};

#endif