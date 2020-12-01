#include "CardFactory.h"
#include <fstream>

CardFactory* CardFactory::cf = nullptr;

void CardFactory::populateList(int amt, Card* c) {
	for (int i = 0; i < amt; i++) {
		cardLst.push_back(c);
	}
}

CardFactory::CardFactory() {
	//Blue Init
	Blue* blue = new Blue();
	cardMapping[blue->getFirst()] = blue;
	populateList(20, blue);

	//Chili Init
	Chili* chili = new Chili();
	cardMapping[chili->getFirst()] = chili;
	populateList(18, chili);

	//Stink Init
	Stink* stink = new Stink();
	cardMapping[stink->getFirst()] = stink;
	populateList(16, stink);

	//Green Init
	Green* green = new Green();
	cardMapping[green->getFirst()] = green;
	populateList(14, green);
	
	//Soy Init
	Soy* soy = new Soy();
	cardMapping[soy->getFirst()] = soy;
	populateList(12, soy);
	
	//Black Init
	Black* black = new Black();
	cardMapping[black->getFirst()] = black;
	populateList(10, black);

	//Red Init
	Red* red = new Red();
	cardMapping[red->getFirst()] = red;
	populateList(8, red);
	
	//Green Init
	Garden* garden = new Garden();
	cardMapping[garden->getFirst()] = garden;
	populateList(6, garden);
}

/*
This method is intended to be used for Card retrieval
from a given abbreviated, one character card identifier
ie. Stink = S
	Blue = B
	Soy = s
	...
*/
Card* CardFactory::getCard(char abbr) const {
	auto currentPos = cardMapping.find(abbr);
	if (currentPos != cardMapping.end()) {
		return currentPos->second;
	} else {
		return nullptr;
	}
}

CardFactory* CardFactory::getFactory() {
	if (cf == nullptr) {
		cf = new CardFactory();
		return cf;
	}
	return cf;
}

CardFactory::~CardFactory() {
	for (auto it = cardMapping.begin(); it != cardMapping.end(); it++) {
		delete it->second;
	}
}

//Deck CardFactory::getDeck() {
//	std::shuffle(cardLst.begin(), cardLst.end(), defaultRandomEng);
	
//	std::ofstream outFile;
//	outFile.open(getFileName(), std::ofstream::trunc);
	//Stream the current contents of the shuffled card list into a file
//	for (Card* c : cardLst) {
//		outFile << c->getFirst() << std::endl;
//	}
//	outFile.close();
 
//	std::ifstream inFile{ getFileName(), std::ifstream::in };
//	return Deck{ inFile, this };
//}


