#include "CardFactory.h"
#include "Deck.h"
#include <fstream>


CardFactory* CardFactory::cf = nullptr;

/*
Populate a cardLst with duplicate Card pointer entries, n amount of times.
*/
void CardFactory::populateList(int n, Card* c) {
	for (int i = 0; i < n; i++) {
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
If a Card cannot be mapped to the character, returns NULLPTR
*/
Card* CardFactory::getCard(char abbr) const {
	auto currentPos = cardMapping.find(abbr);
	if (currentPos != cardMapping.end()) {
		return currentPos->second;
	} else {
		return nullptr;
	}
}

/*
Fetches the Singleton CardFactory instance. If it does not exist, create a new one,
otherwise, fetch the existing one.
*/
CardFactory* CardFactory::getFactory() {
	if (cf == nullptr) {
		cf = new CardFactory();
		return cf;
	}
	return cf;
}

CardFactory::~CardFactory() {
	cardLst.clear();
	//Destroys unique Card pointer instances from cardMapping
	for (auto it = cardMapping.begin(); it != cardMapping.end(); it++) {
		std::cout << "DELETING " << it->second->getName();
		
		//TODO: Figure out why this won't delete properly
		Card* toDelete = it->second;
		delete toDelete;
	}
}

Deck CardFactory::getDeck() {
	//Randomly shuffle deck
	std::shuffle(cardLst.begin(), cardLst.end(), defaultRandomEng);
	
	//Since Deck's only constructor requires reading from an istream,
	//the intuition here is to store the abbreviations of each card in 
	//the shuffled list into a file for the deck to inevitably read
	std::ofstream outFile;
	outFile.open(getFileName(), std::ofstream::trunc);
	for (Card* c : cardLst) {
		outFile << c->getFirst() << std::endl;
	}
	outFile.close();
 
	//Create an ifstream instance of the file we recently populated and
	//construct a Deck instance
	std::ifstream inFile { getFileName(), std::ifstream::in };
	Deck generatedDeck { inFile, this };
	return generatedDeck;
}


