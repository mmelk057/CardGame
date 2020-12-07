#include <iostream>
#include <map> 
#include <climits>
#include <vector>
#include <exception>
#include <string>
#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include "TradeArea.h"
#include "Player.h"
#include "Table.h"
#include "Loader.h"

void lineBreak() {
	std::cout << "-------" << std::endl;
}

void displayTable(Table& table) {
	std::cout << "Current Table State: " << std::endl;
	lineBreak();
	std::cout << table;
}

/*
* General purpose process for selecting a user's decision
*/
int UserChoice(std::vector<std::string> choices) {
	while (true) {
		int i = 1;
		for (std::string choice : choices) {
			std::cout << i << ". " << choice << std::endl;
			i++;
		}
		std::cout << "Please choose an option" << std::endl;
		std::string input;
		std::getline( std::cin >> std::ws , input);
		int userChoice = 0;
		
		try {
			userChoice = stoi(input);
		} catch (std::exception e) {
			std::cout << "Invalid choice" << std::endl<<std::endl;
			continue;
		}
		
		if (userChoice > 0 && userChoice <= choices.size()) {
			return userChoice;
		} else {
			std::cout << "Invalid choice" << std::endl;
		}
	}
}

/*
* Process to play on behalf of a player
*/
void playPlayer(Player& player, Deck& deck, TradeArea& tradeArea, DiscardPile& discardPile) {
	//Player draw
	std::cout << player.getName() << "'s turn" << std::endl;
	std::cout << player;
	lineBreak();
	Card* draw = deck.draw();
	std::cout << "You Drew " << draw->getName() << std::endl;
	std::cout << "Deck Size --> " << deck.size() << std::endl;
	std::cout << "Trade Area Size -->" << tradeArea.numCards() << std::endl;
	lineBreak();
	//IF TradeArea is not empty , ++ Cards from Trade Area to Chains or Discard Them
	if (tradeArea.numCards() > 0) {
		std::cout << "Cards in Trade Area: " << tradeArea << std::endl;
		int choice = UserChoice({ "Begin Trading", "Done Trading" });
		//START TRADING
		if (choice == 1) {
			std::list<std::string> cardOptions = tradeArea.getUnique();
			for(std::string toTrade: cardOptions) {
				//Note: If you finish trading, the remaining cards will remain in the trade area
				std::cout << "Current Card: " << toTrade << std::endl;
				lineBreak();
				int tradeChoice = UserChoice({ "Take Card", "Discard Card", "Finish Trading" });
				if (tradeChoice == 1) {
					Card* card = tradeArea.trade(toTrade);
					bool addStatus = player.addToChain(card);
					//This means we were unable to add a chain
					if (!addStatus) {
						//We need to remove a chain
					}
					//We trade all the cards in the trade area of a given type
					while (tradeArea.legal(card)) {
						tradeArea.trade(toTrade);
						player.addToChain(card);
					}
				}
				else if (tradeChoice == 2) {
					//If we choose to discard, we do not add the card to a player's chain
					tradeArea.trade(toTrade);
				}
				else {
					break;
				}
			}
		}

		//PLAY TOPMOST CARD

		//IF CHAIN IS ENDED, CARDS FOR CHAIN ARE REMOVED --> USE PLAYER.TIECHAIN()

		//PLAYER CHOOSES WHETHER TO PLAY TOPMOST CARD OR NOT

		//IF CHAIN IS ENDED, CARDS FOR CHAIN ARE REMOVED --> USE PLAYER.TIECHAIN()

		//IF PLAYER DECIDES, SHOW PLAYER'S FULL HAND, PICK AN ARBITRARY CARD
			//DISCARD THE ARBITRARY CARD FROM PLAYER, THEN PLACE IT INSIDE THE DISCARD PILE

	}
}

int main()
{
	//Get CardFactory
	CardFactory* cf = CardFactory::getFactory();
	
	Loader loader = Loader();
	loader.loadState();
	Table& table = loader.getTable();
	
	int choice = UserChoice({ "New Game", "Load Saved Game" });
	if (choice == 1) {
		std::string name1,name2;
		std::cout << "Enter First Player's Name: " << std::endl;
		std::cin >> name1;
		std::cout << "Enter Second Player's Name: " << std::endl;
		std::cin >> name2;
		//Since the state of a table is deleted after it is loaded, there is no previous
		//state if we load it a second time; therefore, we end up with a new table
		loader.loadState(name1, name2);
	}

	DiscardPile& discardPile = table.getDiscardPile();
	TradeArea& tradeArea = table.getTradeArea();
	Deck& deck = table.getDeck();


	while (!deck.empty()) {
		int pauseChoice = UserChoice({ "Pause Game", "Continue" });
		if (pauseChoice == 1) {
			loader.saveState();
			break;
		}
		displayTable(table);
		playPlayer(table.getPlayerOne(), deck, tradeArea, discardPile);
		displayTable(table);
		playPlayer(table.getPlayerTwo(), deck, tradeArea, discardPile);
	}

	return 1;
}
