#include "Player.h"

//Declare the Max # of Chains
const int Player::MAX_CHAINS = 3;

std::ostream& operator<<(std::ostream& os, const Player& player) {
	bool flag = false;
	os << player.name << "	" << player.coins << " coins" << std::endl;
	for (ChainBase const* iter : player.chains) {
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

Player & Player::operator+=(int c) {
	coins += c;
	return *this;
}

Player::Player(std::string& s) {
	name = s;
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

void Player::addChain(ChainBase* cb) {
	chains.push_back(cb);
}

void Player::addCard(Card *c) {
	hand += c;
}

void Player::printHand(std::ostream & os, bool wholeHand) const {
	//Verify method
	if (wholeHand) {
		os << hand;
	}
	else {
		os << hand.top();
	}
}
