#include "Chain.h"

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


/*
* Print a given chain type
*/
template <typename T>
std::ostream& Chain<T>::print(std::ostream& os) const {
	int len = static_cast<int>(cards.size());
	if (len == 0) {
		os << "Empty Chain";
	}
	else {
		T* card = cards.front();
		os << card->getName() << "   ";
		for (int i = 0; i < cards.size(); i++) {
			os << " " << card->getFirst();
		}
	}
	return os;
};

template <typename T>
Chain<T>::Chain(std::istream& is, const CardFactory* cf) {
	//TODO LOAD CARDS FROM is
	cards = {};
};

template <typename T>
Chain<T>& Chain<T>::operator+= (Card* c) {
	T* temp = dynamic_cast<T*>(c);
	if (temp) {
		cards.push_back(temp);
		T* card = cards.front();
		if ( cards.size() >= card->getCardsPerCoin(4) ) {
			//Sell chain
			int s = sell();
		}
	}
	else {
		throw "IllegalType";
	}
	return *this;
};

template <typename T>
int Chain<T>::sell() const {
	T* card = cards.front();
	int len = static_cast<int>(cards.size());
	for (int i = 4; i > 0; i--) {
		if (len >= card->getCardsPerCoin(i)) {
			//TODO ACTUALLY SELL CHAIN
			return i;
		}
	}
	return 0;
};