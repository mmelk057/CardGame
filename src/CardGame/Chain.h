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
		//############# STATE METHODS #####################
		virtual const Card* getReference() = 0;
		virtual const int getChainSize() = 0;
		//#################################################

		virtual std::ostream& print(std::ostream&) const = 0;
		virtual ChainBase& addToChain(Card*) = 0;
		friend std::ostream& operator<<(std::ostream&, const ChainBase&);
		ChainBase& operator+= (Card*);
};


template <class T>
class Chain : public ChainBase {
	static_assert((std::is_base_of<Card, T>::value), "T must be of type Card");
	private:
		T* reference = nullptr;

		std::vector<T*> cards{};
		std::ostream& print(std::ostream&) const;
	public:
		const int getChainSize() {
			return static_cast<int>(cards.size());
		};
		const Card* getReference() {
			return dynamic_cast<Card*>(reference);
		};

		int sell() const;
		ChainBase& addToChain(Card*);
		Chain<T>& operator+= (Card*);
		Chain(std::istream&, const CardFactory*);
		Chain(T* ref) : reference(ref) {};
		~Chain() = default;
};

#endif