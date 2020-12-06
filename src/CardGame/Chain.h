#ifndef CHAIN_H
#define CHAIN_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <vector>
#include "Cards.h"
#include "CardFactory.h"

class ChainBase {
public:
	virtual std::ostream& print(std::ostream&) const = 0;
	friend std::ostream& operator<<(std::ostream&, const ChainBase&);
};

template <typename T>
class Chain : public ChainBase {
	private:
		std::vector<T*> cards{};
		std::ostream& print(std::ostream&) const;
	public:
		int sell() const;
		Chain<T>& operator+= (Card*);
		Chain(std::istream&, const CardFactory*);
		~Chain() = default;
};

#endif