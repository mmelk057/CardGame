#pragma once
#include <iostream>
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
public:
	Chain(istream&, const CardFactory*);
	Chain<T>& operator+=(Card*);
	int sell();
	friend ostream& operator<<(ostream& os, const Chain& c);
	~Chain();
private:
	vector<T>
};