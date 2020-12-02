#include "Chain.h"

using namespace std;

template <typename T>
Chain<T>::Chain(istream & is, const CardFactory * cf)
{
	//TODO LOAD CARDS FROM is
	cards = {};
}

template <typename T>
Chain<T>& Chain<T>::operator+=(Card* c){
	T* temp = dynamic_cast<T*> (c);
	if (temp) {
		cards.push_back(temp);
		cout<<temp->getName();
		Card* card = cards.front();
		if (cards.size()>=card->getCardsPerCoin(4)) {
			cout << sell();
		}
	}
	else
	{
		throw "IllegalType";
	}
	return *this;
}

template <typename T>
int Chain<T>::sell() const{
	Card* card = cards.front();
	int len = cards.size();
	for (int i = 4; i > 0; i--) {
		if (len >= card->getCardsPerCoin(i)) {
			//TODO ACTUALLY SELL CHAIN
			return i;
		}
	}
	return 0;
}

template class Chain<Blue>;
template class Chain<Chili>;
template class Chain<Stink>;
template class Chain<Green>;
template class Chain<Soy>;
template class Chain<Black>;
template class Chain<Garden>;
template class Chain<Red>;