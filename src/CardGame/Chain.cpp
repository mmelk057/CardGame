#include "Chain.h"
#include "Cards.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

template class Chain<Blue>;
template class Chain<Chili>;
template class Chain<Stink>;
template class Chain<Green>;
template class Chain<Soy>;
template class Chain<Black>;
template class Chain<Garden>;
template class Chain<Red>;

/*
* Overload of output stream operator
*/
std::ostream& operator<< (std::ostream& os, const ChainBase& chainBase) {
	chainBase.print(os);
	return os;
};
ChainBase & ChainBase::operator+=(Card * c)
{
	addToChain(c);
	return *this;
}

/*
* Recover a chain.
* Stream is of the given format: "B4", "S12", etc.
*/
template <class T>
Chain<T>::Chain(std::istream& is, const CardFactory* cf) {
	//GET CARD TYPE
	std::string input;
	std::getline(is, input);
	char cardType = input.c_str()[0];
	reference = dynamic_cast<T*>(cf->getCard(cardType));
	if (reference == nullptr) {
		throw std::invalid_argument("Invalid card type provided. Unable to build Chain!");
	}
	else {
		//GET NUMBER OF CARDS
		int numberOfCards = std::stoi(input.substr(1));

		//INSERT CARDS
		for (int i = 0; i < numberOfCards; i++) {
			cards.push_back(reference);
		}
	}
};

/*
* Print a given chain type
*/
template <class T>
std::ostream& Chain<T>::print(std::ostream& os) const {
	int len = static_cast<int>(cards.size());
	if (len == 0) {
		os << "Empty Chain";
	}
	else {
		/*T* card = cards.front();
		os << card->getName() << "   ";
		for (int i = 0; i < cards.size(); i++) {
			os << " " << card->getFirst();
		}*/
		os<<toString();
	}
	return os;
};

template<class T>
std::string Chain<T>::toString() const
{
	T* card = cards.front();
	std::string ret = card->getName() + "   ";
	
	for (int i = 0; i < cards.size(); i++) {
		ret += " ";
		ret += card->getFirst();
	}
	return ret;
}

template<class T>
ChainBase & Chain<T>::addToChain(Card *c)
{
	*this += c;
	return *this;
}
template <class T>
Chain<T>& Chain<T>::operator+= (Card* c) {
	T* temp = dynamic_cast<T*>(c);
	if (temp) {
		cards.push_back(temp);
		T* card = cards.front();
		//if ( cards.size() >= card->getCardsPerCoin(4) ) {
		//	//Sell chain
		//	int s = sell();
		//}
	}
	else {
		throw "IllegalType";
	}
	return *this;
};

template <class T>
int Chain<T>::sell() const {
	int len = static_cast<int>(cards.size());
	for (int i = 4; i > 0; i--) {
		if (len >= reference->getCardsPerCoin(i)) {
			return i;
		}
	}
	return 0;
};