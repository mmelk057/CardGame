#pragma once
#include "Cards.h"
#include "CardFactory.h"
using namespace std;

template <typename T>

//class Chain_base {
//public:
//
//};
class Chain
{
private:
	vector<T*> cards;
public:
	Chain(istream&, const CardFactory*);
	Chain<T>& operator+=(Card*);
	int sell() const;
	//friend ostream& operator<<(ostream&, const Chain&);
	friend ostream & operator<<(ostream & os, const Chain<T>& c)
	{
		int len = c.cards.size();
		if (len == 0) {
			os << "Empty Chain";
		}
		else {
			Card* card = c.cards.front();
			os << card->getName() << "   ";
			for (int i = 0; i < c.cards.size(); i++) {
				os << " " << card->getFirst();
			}
		}
		return os;
	}
	~Chain() = default;
};