#ifndef TRADEAREA_H
#define TRADEAREA_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <list>
#include <iostream>
#include <string>
#include "Cards.h"
#include "CardFactory.h"

class Loader;

class TradeArea {
	friend class Loader;
	public:
		TradeArea(std::istream&, const CardFactory*);
		TradeArea& operator+=(Card*);
		bool legal(Card*) const;
		Card* trade(std::string);
		int numCards() const;
		std::list<std::string> getUnique();
		friend std::ostream & operator<<(std::ostream&, const TradeArea&);
		TradeArea() = default;
		~TradeArea() = default;
	private:
		std::list<Card*> cards{};
};

#endif