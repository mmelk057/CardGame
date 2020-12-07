#ifndef CHAIN_H
#define CHAIN_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <type_traits>
#include <vector>
#include "Cards.h"
#include "CardFactory.h"

class ChainBase {
public:
	virtual std::ostream& print(std::ostream&) const = 0;
	virtual ChainBase& addToChain(Card*) = 0;
	virtual std::string toString() const = 0;
	virtual int sell() const = 0;
	friend std::ostream& operator<<(std::ostream&, const ChainBase&);
	ChainBase& operator+= (Card*);
};

template <class T>
class Chain : public ChainBase {
	static_assert((std::is_base_of<Card, T>::value), "T must be of type Card");
	private:
		std::vector<T*> cards{};
		std::ostream& print(std::ostream&) const;
	public:
		int sell() const;
		ChainBase& addToChain(Card*);
		Chain<T>& operator+= (Card*);
		Chain(std::istream&, const CardFactory*);
		std::string toString() const;
		Chain() = default;
		~Chain() = default;
};

#endif