#pragma once
#include <string>
#include "Chain.h"
#include "Hand.h"
#include "Cards.h"

using namespace std;
class Players
{
public:
	Players(std::string&);
	Players(istream&, const CardFactory*);
	string getName() const;
	int getNumCoins() const;
	Players& operator+=(int);
	int getMaxNumChains() const;
	int getNumChains() const;
	Chain_base& operator[](int i);
	void buyThirdChain();
	void printHand(std::ostream&, bool);
	friend ostream & operator<<(ostream &, Players);
	void addChain(Chain_base*);
	~Players() = default;
private:
	int coins;
	string name;
	vector<Chain_base*> chains;
	int chainLimit = 2;
	const int MAX_CHAINS = 3;
	Hand hand;
};

