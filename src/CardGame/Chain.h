#pragma once
#include "Cards.h"
#include "CardFactory.h"
using namespace std;

class Chain_base {
public:
	virtual ostream& insertString(ostream & os) const {
		return os;
	}
	friend ostream& operator<<(ostream& os, const Chain_base& cb) {
		return cb.insertString(os);
	}
};

template <typename T>
class Chain : public Chain_base
{
private:
	vector<T*> cards;
public:
	Chain(istream&, const CardFactory*);
	Chain<T>& operator+=(Card*);
	int sell() const;
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
	ostream& insertString(ostream & os) const;
	~Chain() = default;
};