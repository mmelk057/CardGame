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
	/*Loader loader = Loader();
	loader.loadState();
	Table& table = loader.getTable();
	table.getTradeArea() += table.getDeck().draw();
	loader.saveState();*/
	//#############################################################################
	Table table;
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
		lineBreak();
		if (choice == 2) {//Save game
			//TODO exit game
			std::cout << "Save game"<< std::endl;
			continue;
		}
		for (Player* currPlayer : { &table.getPlayerOne() , &table.getPlayerTwo() }) {
			//Table print
			std::cout <<"Table: " <<std::endl<< table << std::endl << std::endl;

			//Player draw
			std::cout << currPlayer->getName() << "'s turn" << std::endl;
			Card* draw = deck->draw();
			currPlayer->addCard(draw);
			std::cout << "You drew " << draw->getName() << std::endl;

			if (tradeArea->numCards() > 0) {
				//Trading step
				choice = 0;
				while (tradeArea->numCards() > 0) {
					std::cout << "Trading:" << std::endl;
					choice = UserChoice({ "Take cards", "Discard cards", "Done trading" });
					lineBreak();
					if (choice == 3) break; //Done trading
					int tradeChoice = 0;

					while (tradeArea->numCards() > 0) {
						std::cout << "Table: " << std::endl << table << std::endl;
						//Get unique cards in the trading area
						std::list<std::string> options = tradeArea->getUnique();
						if (choice == 1) {
							options.push_front("Done taking");
						}
						else {
							options.push_front("Done discarding");
						}
						std::vector<std::string> v{ options.begin(), options.end() };
						tradeChoice = UserChoice(v);
						if (tradeChoice == 1) {//Done trading/discarding
							lineBreak();
							break;
						}
						else {//Trade card
							Card* drawn = tradeArea->trade(v[tradeChoice - 1]);
							std::cout << drawn->getName() << std::endl;
							lineBreak();
							if (choice == 1 && !currPlayer->addToChain(drawn)) {//take card mode
								std::cout << "Cannot add to existing chains" << std::endl;
								//Add back to trading pile
								*tradeArea += drawn;
							}
							else if (choice == 2) {
								*discardPile += drawn;
							}
						}
					}
					std::cout << "Table: " << std::endl << table << std::endl;
					
				}

			}
			
			//Play top card, option to do a second time
			std::cout << "Trading is done! Now you play the top card of your hand." << std::endl;
			
			for (int i = 0; i < 2; i++) {
				Card* drawn = currPlayer->playTopCard();
				std::cout << "Played " << drawn->getName()<<std::endl;
				if (!currPlayer->addToChain(drawn)) {//Cannot add top card to chains
					std::cout << "Cannot add to existing chains. Which would you like to sell?" << std::endl << *currPlayer <<std::endl;
					choice = UserChoice(currPlayer->getChainStrings());
					*currPlayer += (*currPlayer)[choice - 1].sell();
					currPlayer->removeChain(choice - 1);
					currPlayer->addToChain(drawn);
					lineBreak();
				}
				else {
					std::cout << "Added to existing chain!" << std::endl;
				}
				std::cout << *currPlayer << std::endl;
				if (i == 0) {
					std::cout << "Would you like to draw again?" << std::endl;
					choice = UserChoice({ "Yes", "No" });
					lineBreak();
					if (choice == 2) {
						break;
					}
				}
			}
			
		}
		break;
	}
	
	 
	/*
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
