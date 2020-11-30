#include "Cards.h"
#include <map> 
#include <climits>

int fetchCoinsPerCard(const std::map<int, int>& value_mappings, int coins) {
	int * positions = new int[coins + 1];
	positions[0] = 0;
	for (int i = 1; i <= coins; i++) {
		std::map<int, int>::const_iterator curr = value_mappings.find(i);
		if (curr != std::end(value_mappings)) {
			positions[i] = curr->second;
		}
		else {
			positions[i] = INT_MAX;
		}
	}
	for (int i = 1; i <= coins; i++) {
		for (std::map<int, int>::const_iterator it = value_mappings.begin(); it != value_mappings.end(); it++) {
			int currentCoinValue = it->first;
			int currentCardsValue = it->second;
			if ((currentCoinValue <= i)) {
				int previousStoredValue = positions[i - currentCoinValue];
				if (positions[i] > (previousStoredValue + currentCardsValue)) {
					positions[i] = previousStoredValue + currentCardsValue;
				}
			}
		}
	}

	return positions[coins] == INT_MAX ? -1 : positions[coins];
}

/* Non-member function impl of left-shift operator to stream Card class */
inline std::ostream& operator << (ostream& os, const Card& c) {
	c.print(os);
	return os;
}


//######   Blue Card Start  ##############################################
int Blue::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 4;
	coinsToCards[2] = 6;
	coinsToCards[3] = 8;
	coinsToCards[4] = 10;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Blue::getName() {
	return typeid(this).name();
}

void Blue::print(ostream& out) const {
	out.write(typeid(this).name(), 1);
}

//#######  Chili Card Start ###############################################
int Chili::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 6;
	coinsToCards[3] = 8;
	coinsToCards[4] = 9;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Chili::getName() {
	return typeid(this).name();
}

void Chili::print(ostream& out) const {
	out.write(typeid(this).name(), 1);
}

//######## Stink Card Start ###############################################
int Stink::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 5;
	coinsToCards[3] = 7;
	coinsToCards[4] = 8;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Stink::getName() {
	return typeid(this).name();
}

void Stink::print(ostream& out) const {
	out.write(typeid(this).name(), 1);
}

//######### Green Card Start ##############################################
int Green::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 5;
	coinsToCards[3] = 6;
	coinsToCards[4] = 7;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Green::getName() {
	return typeid(this).name();
}

void Green::print(ostream& out) const {
	out.write(typeid(this).name(), 1);
}

//######### Soy Card Start ################################################
int Soy::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 4;
	coinsToCards[3] = 6;
	coinsToCards[4] = 7;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Soy::getName() {
	return typeid(this).name();
}

void Soy::print(ostream& out) const {
	char lowerFirst = tolower((typeid(this).name())[0]);
	out.write(&lowerFirst, 1);
}

//########## Black Card Start #############################################
int Black::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 4;
	coinsToCards[3] = 5;
	coinsToCards[4] = 6;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Black::getName() {
	return typeid(this).name();
}

void Black::print(ostream& out) const {
	char lowerFirst = tolower((typeid(this).name())[0]);
	out.write(&lowerFirst, 1);
}

//########## Red Card Start ###############################################
int Red::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 3;
	coinsToCards[3] = 4;
	coinsToCards[4] = 5;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Red::getName() {
	return typeid(this).name();
}

void Red::print(ostream& out) const {
	out.write(typeid(this).name(), 1);
}

//########### Garden Card Start #############################################
int Garden::getCardsPerCoin(int coins) {
	std::map<int, int> coinsToCards;
	coinsToCards[2] = 2;
	coinsToCards[3] = 3;
	return fetchCoinsPerCard(coinsToCards, coins);
}

string Garden::getName() {
	return typeid(this).name();
}

void Garden::print(ostream& out) const {
	char lowerFirst = tolower((typeid(this).name())[0]);
	out.write(&lowerFirst, 1);
}
