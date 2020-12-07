#ifndef HAND_H
#define HAND_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <queue>
#include <list>
#include <sstream>
#include "CardFactory.h"
#include "Cards.h"

//Forward Declaring
class Card;
class CardFactory;
class Loader;

class Hand {
	friend class Loader;
	private:
		std::queue<Card*, std::list<Card*>> queue{};
		void display(std::ostream&);

	public:
		friend std::ostream& operator<< (std::ostream&, Hand&);
	
		Card* play();
		Card* top() const;

		Card* operator[](int);
		Hand& operator += (Card*);
		Hand(std::istream&, const CardFactory*);
		Hand() = default;
		~Hand() = default;
};

#endif