#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include "Cards.h"
#include "Deck.h"

//Forward declare
class Card;
class Deck;

class CardFactory
{
	private:
		//Constructor must be private - Cannot allow users to build new CardFactories
		CardFactory();
		std::random_device device{};
		std::default_random_engine defaultRandomEng{device()};
		
		//Card List - Should always contain 104 Cards
		std::vector<Card*> cardLst {};

		//Map of reusable Card pointers
		std::map<char, Card*> cardMapping{};
		
		//Helper function - populates cardLst a # of times with 
		//one particular Card pointer
		void populateList(int, Card *);
		
		//Singleton CardFactory instance
		static CardFactory* cf;

		//This file will be used to build new decks
		const std::string fileName = "CardFactoryState.txt";
	
	public:
		Deck getDeck();
		std::string getFileName() const {
			return fileName;
		}

		static CardFactory* getFactory();
		Card* getCard(char abbr) const;
		~CardFactory();
};

#endif