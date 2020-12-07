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
int main()
{
	//Get card factory
	CardFactory* cf = CardFactory::getFactory();
	
	//###################### TEMPORARY CODE - TESTING PURPOSES ####################
	Loader loader = Loader();
	loader.loadState();
	Table& table = loader.getTable();
	for (int i = 0; i < 15; i++) {
		table.getPlayerOne().addToChain(table.getDeck().draw());
		table.getPlayerTwo().addToChain(table.getDeck().draw());
	}
	loader.saveState();
	//#############################################################################

	//Testing
	int choice = UserChoice({ "New game", "Load game from file" });
	if (choice == 1) {//New game initialization
		std::string name1,name2;
		std::cout << "Enter player name 1" << std::endl;
		std::cin >> name1;
		std::cout << "Enter player name 2" << std::endl;
		std::cin >> name2;
		table = Table(name1, name2, cf);
	}
	else { //Load game from file
		table = Table(std::cin, cf);
	}

	//Pointers to table components
	DiscardPile* discardPile = &table.getDiscardPile();
	TradeArea* tradeArea = &table.getTradeArea();
	Deck* deck = &table.getDeck();

	std::string winner = "NONE";
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	*tradeArea += deck->draw();
	while (!table.win(winner)) {
		//Save or continue game
		lineBreak();
		choice = UserChoice({"Continue", "Save and exit"});
		if (choice == 2) {//Save game
			//TODO exit game
			std::cout << "Save game"<< std::endl;
			continue;
		}
		for (Player currPlayer : { table.getPlayerOne() , table.getPlayerTwo() }) {
			//Table print
			lineBreak();
			std::cout <<"Table: " <<std::endl<< table << std::endl << std::endl;

			//Player draw
			std::cout << currPlayer.getName() << "'s turn" << std::endl;
			Card* draw = deck->draw();
			std::cout << "You drew " << draw->getName() << std::endl;
			std::cout << deck->size() << std::endl;
			std::cout << tradeArea->numCards() << std::endl;
			
			if (tradeArea->numCards() > 0) {
				//Trading step
				choice = 0;
				while (choice != 3 && tradeArea->numCards() > 0) {
					std::cout << "Trading:" << std::endl;
					choice = UserChoice({ "Take cards", "Discard cards", "Done trading" });
					std::cout << std::endl;
					int tradeChoice = 0;
					std::cout << "You: " << currPlayer << std::endl;

					while (tradeArea->numCards() > 0) {
						std::cout << "Trade Area: " << *tradeArea << std::endl;
						//Get unique cards in the trading area
						std::list<std::string> options = tradeArea->getUnique();
						if (choice == 1) {
							options.push_front("Done trading");
						}
						else {
							options.push_front("Done discarding");
						}
						std::vector<std::string> v{ options.begin(), options.end() };
						tradeChoice = UserChoice(v);
						if (tradeChoice == 1) {//Done trading
							break;
						}
						else {//Trade card
							Card* drawn = tradeArea->trade(v[tradeChoice - 1]);
							std::cout << drawn->getName() << std::endl << std::endl;
							if (choice == 1 && !currPlayer.addToChain(drawn)) {//take card mode
								std::cout << "Cannot add to existing chains" << std::endl;
								*tradeArea += drawn;
							}
						}
						std::cout << "You: " << currPlayer << std::endl;
					}
					
				}

			}
			//TODO Play topmost card from Hand.
			/*The player then plays the topmost card from his/her hand. The card must be added to a chain with
			the same beans.If the player has currently no such chain on the table, an old chain on the table
			will have to be tied and sold, and a new chain must be started.If the chain has not reached a
			sufficient length, a player may receive 0 coins. May repeat once
			*/
		}
		break;
	}
	
	 
	/*
For each Player
If chain is ended, cards for chain are removed and player receives coin(s).
If player decides to
Play the now topmost card from Hand.
If chain is ended, cards for chain are removed and player receives coin(s).
If player decides to
Show the player's full hand and player selects an arbitrary card
Discard the arbitrary card from the player's hand and place it on the discard pile.
Draw three cards from the deck and place cards in the trade area
while top card of discard pile matches an existing card in the trade area
draw the top-most card from the discard pile and place it in the trade area
end
for all cards in the trade area
if player wants to chain the card
chain the card.
else
card remains in trade area for the next player.
end
Draw two cards from Deck and add the cards to the player's hand (at the back).
end
end
	*/
	return 1;
}
