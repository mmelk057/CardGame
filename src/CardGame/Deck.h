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
class Loader;

class Deck: private std::vector<Card*> {
	friend class Loader;
	private:
		typedef std::vector<Card*> CardList;
		using CardList::begin;
		using CardList::end;

		void display(std::ostream&) const;
	public:
		friend std::ostream& operator<< (std::ostream& os, const Deck& d);

		using CardList::size;
		using CardList::empty;
		using CardList::front;

		Card* draw();
		Deck() = default;
		Deck(std::istream& is, const CardFactory* cf);
		~Deck() = default;
};

#endif

