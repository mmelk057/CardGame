#include "Players.h"


Players & Players::operator+=(int c)
{
	coins += c;
	return *this;
}

ostream & operator<<(ostream & os, Players p)
{
	bool flag = false;
	os << p.name << "	" << p.coins << " coins" << endl;
	for (Chain_base const* iter : p.chains) {
		if (flag) {
			os << endl;
		}
		else {
			flag = true;
		}
		os << *iter;
	}
	return os;
}

Players::Players(std::string & s)
{
	name = s;
	//Create hand
}

Players::Players(istream &, const CardFactory *)
{
	//TODO create from istream
}

string Players::getName() const
{
	return name;
}

int Players::getNumCoins() const
{
	return coins;
}

int Players::getMaxNumChains() const
{
	return chainLimit;
}

int Players::getNumChains() const
{
	return chains.size();
}

Chain_base & Players::operator[](int i)
{
	return *chains[i];
}

void Players::buyThirdChain()
{
	if (chainLimit >= MAX_CHAINS) {
		throw "MaxChainsReached";
	}
	if (coins >= 3) {
		chainLimit = 3;
		coins -= 3;
	}
	else {
		throw "NotEnoughCoins";
	}
}

void Players::addChain(Chain_base* cb)
{
	chains.push_back(cb);
}

void Players::printHand(std::ostream & os, bool wholeHand)
{
	//Verify method
	if (wholeHand) {
		os << hand;
	}
	else {
		os << hand.top();
	}
}
