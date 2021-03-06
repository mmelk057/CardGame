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
		bool operator<(Card const &);
		bool operator>(Card const &);
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
		virtual ~Card() = default;
	
		//A card cannot copy, nor assign itself to another Card.
		//The CardFactory is responsible for doing this..
		Card(const Card&) = delete;
		void operator=(const Card&) = delete;
	
	protected:	
		virtual void print(std::ostream&) const  = 0;
};

class Blue : public virtual Card {
	public:
		int getCardsPerCoin(int coins) const;
		std::string getName() const;
		char getFirst() const;
		~Blue() = default;
	protected:
		void print(std::ostream&) const;
};

class Chili : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Chili() = default;
	protected:
		void print(std::ostream& out) const;
};

class Stink : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Stink() = default;
	protected:
		void print(std::ostream&) const;
};

class Green : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Green() = default;
	protected:
		void print(std::ostream&) const;
};

class Soy : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Soy() = default;
	protected:
		void print(std::ostream&) const;
};

class Black : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Black() = default;
	protected:
		void print(std::ostream&) const;
};

class Red : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Red() = default;
	protected:
		void print(std::ostream&) const;
};

class Garden : public virtual Card {
	public:
		int getCardsPerCoin(int) const;
		std::string getName() const;
		char getFirst() const;
		~Garden() = default;
	protected:
		void print(std::ostream&) const;
};

#endif