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
inline std::ostream& operator << (std::ostream& os, const Card& c) {
	c.print(os);
	return os;
}


//######   Blue Card Start  ##############################################
int Blue::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 4;
	coinsToCards[2] = 6;
	coinsToCards[3] = 8;
	coinsToCards[4] = 10;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Blue::getName() const {
	return "Blue";
}

char Blue::getFirst() const {
	return 'B';
}

void Blue::print(std::ostream& out) const {
	out.put(getFirst());
}

//#######  Chili Card Start ###############################################
int Chili::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 6;
	coinsToCards[3] = 8;
	coinsToCards[4] = 9;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Chili::getName() const {
	return "Chili";
}

char Chili::getFirst() const {
	return 'C';
}

void Chili::print(std::ostream& out) const {
	out.put(getFirst());
}

//######## Stink Card Start ###############################################
int Stink::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 5;
	coinsToCards[3] = 7;
	coinsToCards[4] = 8;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Stink::getName() const {
	return "Stink";
}

char Stink::getFirst() const {
	return 'S';
}

void Stink::print(std::ostream& out) const {
	out.put(getFirst());
}

//######### Green Card Start ##############################################
int Green::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 3;
	coinsToCards[2] = 5;
	coinsToCards[3] = 6;
	coinsToCards[4] = 7;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Green::getName() const {
	return "Green";
}

char Green::getFirst() const {
	return 'G';
}

void Green::print(std::ostream& out) const {
	out.put(getFirst());
}

//######### Soy Card Start ################################################
int Soy::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 4;
	coinsToCards[3] = 6;
	coinsToCards[4] = 7;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Soy::getName() const {
	return "Soy";
}

char Soy::getFirst() const {
	return 's';
}

void Soy::print(std::ostream& out) const {
	out.put(getFirst());
}

//########## Black Card Start #############################################
int Black::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 4;
	coinsToCards[3] = 5;
	coinsToCards[4] = 6;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Black::getName() const {
	return "Black";
}

char Black::getFirst() const {
	return 'b';
}

void Black::print(std::ostream& out) const {
	out.put(getFirst());
}

//########## Red Card Start ###############################################
int Red::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[1] = 2;
	coinsToCards[2] = 3;
	coinsToCards[3] = 4;
	coinsToCards[4] = 5;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Red::getName() const {
	return "Red";
}

char Red::getFirst() const {
	return 'R';
}

void Red::print(std::ostream& out) const {
	out.put(getFirst());
}

//########### Garden Card Start #############################################
int Garden::getCardsPerCoin(int coins) const {
	std::map<int, int> coinsToCards;
	coinsToCards[2] = 2;
	coinsToCards[3] = 3;
	return fetchCoinsPerCard(coinsToCards, coins);
}

std::string Garden::getName() const{
	return "Garden";
}

char Garden::getFirst() const {
	return 'g';
}

void Garden::print(std::ostream& out) const {
	out.put(getFirst());
}
