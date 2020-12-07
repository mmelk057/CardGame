#include "Player.h"
#include <iostream>

//Declare the Max # of Chains
const int Player::MAX_CHAINS = 3;

std::ostream& operator<<(std::ostream& os, const Player& player) {
	bool flag = false;
	os << player.name << "	" << player.coins << " coins" << std::endl;
	for (std::shared_ptr<ChainBase> const& iter : player.chains) {
		if (flag) {
			os << std::endl;
		}
		else {
			flag = true;
		}
		os << *iter;
	}
	return os;
}

Player& Player::operator+=(int c) {
	coins += c;
	return *this;
}

Player::Player(std::string& s) {
	name = s;
	coins = 0;
}

std::string Player::getName() const {
	return name;
}

int Player::getNumCoins() const {
	return coins;
}

int Player::getMaxNumChains() const {
	return chainLimit;
}

int Player::getNumChains() const {
	return static_cast<int>(chains.size());
}

std::vector<std::string> Player::getChainStrings() {
	std::vector<std::string> chainStrs;
	for (std::shared_ptr<ChainBase> & chain : chains) {
		chainStrs.push_back(chain->toString());
	}
	return chainStrs;
}

void Player::removeChain(int i)
{
	chains.erase(chains.begin() + i);
}

Card* Player::removeCard(int i)
{
	return hand[i];
}

ChainBase& Player::operator[](int i) {
	return *(chains[i]);
}

void Player::buyThirdChain() {
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

void Player::addCard(Card *c) {
	hand += c;
}

std::vector<std::string> Player::getHandStrings() {
	return hand.getStrings();
}
void Player::printHand(std::ostream & os, bool wholeHand) {
	//Verify method
	if (wholeHand) {
		os << hand;
	}
	else {
		os << hand.top();
	}
}
std::shared_ptr<ChainBase> newChain(Blue* card) {
	//std::cout << "BLUE CARD" << std::endl;
	return std::make_shared<Chain<Blue>>(card);
}
std::shared_ptr<ChainBase> newChain(Red* card) {
	//std::cout << "RED CARD" << std::endl;
	return std::make_shared<Chain<Red>>(card);
}
std::shared_ptr<ChainBase>  newChain(Chili* card) {
	//std::cout << "Chili CARD" << std::endl;
	return std::make_shared<Chain<Chili>>(card);
}
std::shared_ptr<ChainBase>  newChain(Stink* card) {
	//std::cout << "Stink CARD" << std::endl;
	return std::make_shared<Chain<Stink>>(card);
}
std::shared_ptr<ChainBase>  newChain(Green* card) {
	//std::cout << "Green CARD" << std::endl;
	return std::make_shared<Chain<Green>>(card);
}
std::shared_ptr<ChainBase>  newChain(Soy* card) {
	//std::cout << "Soy CARD" << std::endl;
	return std::make_shared<Chain<Soy>>(card);
}
std::shared_ptr<ChainBase>  newChain(Black* card) {
	//std::cout << "Black CARD" << std::endl;
	return std::make_shared<Chain<Black>>(card);
}
std::shared_ptr<ChainBase>  newChain(Garden* card) {
	//std::cout << "Garden CARD" << std::endl;
	return std::make_shared<Chain<Garden>>(card);
}

std::shared_ptr<ChainBase> newChain(Card* card) {
	Blue* blue = dynamic_cast<Blue*>(card);
	if (blue) {
		return newChain(blue);
	}
	Red* red = dynamic_cast<Red*>(card);
	if (red) {
		return newChain(red);
	}
	Chili* chili = dynamic_cast<Chili*>(card);
	if (chili) {
		return newChain(chili);
	}
	Stink* stink = dynamic_cast<Stink*>(card);
	if (stink) {
		return newChain(stink);
	}
	Green* green = dynamic_cast<Green*>(card);
	if (green) {
		return newChain(green);
	}
	Soy* soy = dynamic_cast<Soy*>(card);
	if (soy) {
		return newChain(soy);
	}
	Black* black = dynamic_cast<Black*>(card);
	if (black) {
		return newChain(black);
	}
	Garden* garden = dynamic_cast<Garden*>(card);
	if (garden) {
		return newChain(garden);
	}
	return NULL;
}
bool Player::addToChain(Card* card) {
	for (std::shared_ptr<ChainBase>& chain : chains) {
		try {
			*chain += card;
			return true;
		}
		catch(const char* e) {
			//std::cout << e << std::endl;
			continue;
		}
	}
	if (getNumChains() != chainLimit) {
		std::shared_ptr<ChainBase> t = newChain(card);
		*t += card;
		chains.push_back(t);
		return true;
	}
	return false;
}

Card * Player::playTopCard()
{
	return hand.play();
}
/*
* Ties & sells a chain from a specific index 
*/
void Player::tieChain(int index) {
	int pos = 0;
	for (auto iterator = chains.begin(); iterator != chains.end(); ++iterator, ++pos) {
		if (pos == index) {
			coins += (*iterator)->sell();
			chains.erase(iterator);
		}
	}
}
