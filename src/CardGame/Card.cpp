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

	return positions[coins];
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


