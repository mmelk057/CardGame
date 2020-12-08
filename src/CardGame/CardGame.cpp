#include <iostream>
#include <map> 
#include <climits>
#include <vector>
#include <exception>
#include <string>
#include <iomanip>
#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include "TradeArea.h"
#include "Player.h"
#include "Table.h"
#include "Loader.h"

void lineBreak() {
	std::cout << "-------------------------" << std::endl;
}

void displayTable(Table& table) {
	std::cout << std::endl << "------------------------" << std::endl;
	std::cout << "| Current Table State: |" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << table;
	lineBreak();
}

void displayPlayer(Player& player) {
	std::cout << std::endl << " ------------------------" << std::endl;
	std::cout << " | Current Player State |" << std::endl;
	std::cout << " ------------------------" << std::endl;
	std::cout << player;
	lineBreak();
}

void displayCard(std::string message, Card* card) {
	std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << message << " " << card->getName() << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl << std::endl;
}

void displayTradeArea(TradeArea& tradeArea) {
	std::cout << std::endl << tradeArea << std::endl;
}

void displayTurn(std::string playerName) {
	std::string full = playerName;
	full += "'s Turn";
	int fillAmountTop = static_cast<int>(full.size())*2;
	int fillAmountRight = static_cast<int>(full.size());
	std::cout << std::endl << std::setfill('*') << std::setw(fillAmountTop) << '\n';
	std::cout << full;
	std::cout << std::setfill('*') << std::setw(fillAmountRight) << '\n';
	std::cout << std::setfill('*') << std::setw(fillAmountTop) << '\n';
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
			userChoice = std::stoi(input);
		} catch (std::exception e) {
			std::cout << "Invalid choice" << std::endl << std::endl;
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
	player += 3;
	displayTurn(player.getName());
	displayPlayer(player);
	Card* draw = deck.draw();
	player.addCard(draw);
	displayCard("You Drew", draw);
	int choice = 0;
	if (player.getMaxNumChains() != 3 && player.getNumCoins()>=3) {
		std::cout << "Would you like to buy a 3rd chain?" << std::endl;
		choice = UserChoice({ "Yes", "No" });
		if (choice == 1) {
			player.buyThirdChain();
		}
	}
	choice = 0;
	//IF TradeArea is not empty , ++ Cards from Trade Area to Chains or Discard Them
	if (tradeArea.numCards() > 0) {
		std::cout << "Cards in Trade Area: " << tradeArea << std::endl;
		choice = UserChoice({ "Begin Trading", "Done Trading" });
		//START TRADING
		if (choice == 1) {
			std::list<std::string> cardOptions = tradeArea.getUnique();
			for(std::string toTrade: cardOptions) {
				//Note: If you finish trading, the remaining cards will remain in the trade area
				std::cout << player<<std::endl;
				std::cout << "Current Card: " << toTrade << std::endl;
				lineBreak();
				int tradeChoice = UserChoice({ "Take Card", "Discard Card", "Finish Trading" });
				
				Card* card = tradeArea.trade(toTrade);
				if (tradeChoice == 1) {
					bool addStatus = player.addToChain(card);
					//This means we were unable to add a chain
					if (!addStatus) {
						tradeArea+=card;
						std::cout << "Could not add. No existing chain"<<std::endl;
					}
					else {
						//We trade all the cards in the trade area of a given type
						while (tradeArea.legal(card)) {
							player.addToChain(tradeArea.trade(toTrade));
						}
					}
				}
				else if (tradeChoice == 2) {
					//If we choose to discard, we do not add the card to a player's chain
					while (tradeArea.legal(card)) {
						discardPile += tradeArea.trade(toTrade);
					}
				}
				else {
					continue;
				}
				
			}
		}
	}
	//Play top card, option to do a second time
	std::cout << "Trading is done! Now you play the top card of your hand." << std::endl;
	for (int i = 0; i < 2; i++) {
		Card* drawn = player.playTopCard();
		displayCard("Played", drawn);
		if (!player.addToChain(drawn)) {//Cannot add top card to chains
			std::cout << "Cannot add to existing chains. Which would you like to sell?" << std::endl;
			displayPlayer(player);
			choice = UserChoice(player.getChainStrings());
			player += player[choice - 1].sell();
			player.removeChain(choice - 1);
			player.addToChain(drawn);
			lineBreak();
		}
		else {
			std::cout << "Added to existing chain!" << std::endl;
		}

		displayPlayer(player);

		if (i == 0) {
			std::cout << "Would you like to draw again?" << std::endl;
			choice = UserChoice({ "Yes", "No" });
			lineBreak();
			if (choice == 2) {
				break;
			}
		}
	}
	std::cout << "Would you like to discard 1 card?" << std::endl;
	choice = UserChoice({ "Yes","No" });
	lineBreak();
	if (choice == 1) {
		player.printHand(std::cout, true);
		std::cout << "Which card would you like to discard?" << std::endl;
		choice = UserChoice(player.getHandStrings());
		lineBreak();
		discardPile += player.removeCard(choice - 1);
		std::cout << std::endl;
	}
	for (int i = 0; i < 3; i++) {
		tradeArea += deck.draw();
	}
	while (discardPile.top() != nullptr && tradeArea.legal(discardPile.top())) {
		tradeArea += discardPile.pickUp();
	}

	std::list<std::string> cardOptions = tradeArea.getUnique();
	for (std::string toTrade : cardOptions) {
		//Note: If you finish trading, the remaining cards will remain in the trade area
		displayTradeArea(tradeArea);
		displayPlayer(player);
		std::cout << "Current Card: " << toTrade << std::endl;
		lineBreak();
		int tradeChoice = UserChoice({ "Take Card", "Skip" });

		
		if (tradeChoice == 1) {
			Card* card = tradeArea.trade(toTrade);
			bool addStatus = player.addToChain(card);
			//This means we were unable to add a chain
			if (!addStatus) {
				std::cout << "Cannot add to existing chains. Which would you like to sell?" << std::endl;
				displayPlayer(player);
				choice = UserChoice(player.getChainStrings());
				player += player[choice - 1].sell();
				player.removeChain(choice - 1);
				player.addToChain(card);
			}
			//We trade all the cards in the trade area of a given type
			while (tradeArea.legal(card)) {
				player.addToChain(tradeArea.trade(toTrade));
			}
		}
		else {
			continue;
		}

	}

	//DRAW TWO CARDS FROM DECK, ADD TO PLAYER'S HAND
	player.addCard(deck.draw());
	player.addCard(deck.draw());
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


	std::string winner = "NONE";
	DiscardPile& discardPile = table.getDiscardPile();
	TradeArea& tradeArea = table.getTradeArea();
	Deck& deck = table.getDeck();

	bool flag = false;
	displayTable(table);
	while (!table.win(winner)) {
		int pauseChoice = UserChoice({ "Pause Game", "Continue" });
		if (pauseChoice == 1) {
			loader.saveState();
			flag = true;
			break;
		}
		playPlayer(table.getPlayerOne(), deck, tradeArea, discardPile);
		displayTable(table);
		playPlayer(table.getPlayerTwo(), deck, tradeArea, discardPile);
		displayTable(table);
	}
	if (flag) {
		return 1;
	}
	if (winner.compare(table.getPlayerOne().getName()) == 0) {
		std::cout << table.getPlayerOne().getName() << " is the winner!";
	}
	else if (winner.compare(table.getPlayerTwo().getName()) == 0) {
		std::cout << table.getPlayerTwo().getName() << " is the winner!";
	}
	else {
		std::cout << "TIE";
	}
	return 1;
}
