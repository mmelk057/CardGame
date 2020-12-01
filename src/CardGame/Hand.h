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

class Hand
{
	private:
		std::queue<Card*, std::list<Card*>> queue{};
		void display(std::ostream&) const;
		static const std::string fileName;
		/*
		Since there are multiple Hand instances, the file name that
		will save the state of any given Hand will be suffixed with the identifier
		provided by a higher level Player instance
		*/
		static std::string getFileName(int identifier) {
			std::ostringstream fileNameS;
			std::ostringstream fileExtS;
			bool found = false;
			for (char nameChar : fileName) {
				if (nameChar != '.' && !found) {
					fileNameS << nameChar;
				}
				else {
					found = true;
					fileExtS << nameChar;
				}
			}
			fileNameS << identifier << fileExtS.str();
			return fileNameS.str();
		}

	public:
		friend std::ostream& operator<< (std::ostream&, const Hand&);
	
		Card* play();
		Card* top();

		//######## These methods ensure Hand state is recovered if previously saved #####
		void saveState(int identifier);
		static Hand recoverState(int identifier);
		//###############################################################################

		Card* operator[](int);
		Hand& operator += (Card*);
		Hand(std::istream&, const CardFactory*);
		Hand() = default;
		~Hand() = default;
};

#endif