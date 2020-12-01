#ifndef DECK_H
#define DECK_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <vector>
#include <iostream>
#include "CardFactory.h"
#include "Cards.h"

//Forward declaring
class Card;
class CardFactory;

class Deck: private std::vector<Card*> {
	private:
		typedef std::vector<Card*> CardList;
		
		void display(std::ostream&) const;
	public:
		friend std::ostream& operator<< (std::ostream& os, const Deck& d);

		using CardList::pop_back;
		using CardList::size;
		using CardList::empty;
		using CardList::back;

		Card* draw();

		Deck(std::istream& is, const CardFactory* cf);
		~Deck() = default;
};

#endif

