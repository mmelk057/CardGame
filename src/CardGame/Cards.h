#ifndef CARDS_H
#define CARDS_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <string>
#include "CardFactory.h"

//Forward declare
class CardFactory;

class Card {
	public:
		friend std::ostream& operator << (std::ostream& os, const Card& c);
	
		/*
		Fetches the amount of cards needed to obtain n amount of coins
		*/
		virtual int getCardsPerCoin(int coins) const = 0;
		
		/*
		Fetches the full class name
		*/
		virtual std::string getName() const = 0;
		
		/*
		Fetches the abbreviated version of the class
		*/
		virtual char getFirst() const = 0;
		
		Card() = default;
	
		//A card cannot copy, nor assign itself to another Card.
		//The CardFactory is responsible for doing this..
		Card(const Card&) = delete;
		void operator=(const Card&) = delete;
	
	protected:
		virtual void print(std::ostream& out) const  = 0;
};

class Blue : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Chili : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Stink : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Green : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Soy : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Black : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Red : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

class Garden : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
	protected:
		void print(std::ostream& out) const;
};

#endif