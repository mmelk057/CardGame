#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <vector>
#include <string>
#include "Cards.h"
#include "CardFactory.h"

class Card;

class DiscardPile
{
	private:
		std::vector<Card*> pile{};
		void print(std::ostream&) const;
		static const std::string fileName;
	public:
		friend std::ostream& operator<< (std::ostream&, const DiscardPile&);

		Card* pickUp();
		Card* top() const;

		//######## These methods ensure DiscardPile state is recovered if previously saved ######
		void saveState();
		static DiscardPile recoverState();
		//#######################################################################################	

		DiscardPile() = default;
		DiscardPile(std::istream&, const CardFactory*);
		DiscardPile& operator+= (Card*);
		~DiscardPile() = default;
};

#endif