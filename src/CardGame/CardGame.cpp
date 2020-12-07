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
	player.addCard(draw);
	std::cout << "You Drew " << draw->getName() << std::endl;
	lineBreak();
	int choice = 0;
	//IF TradeArea is not empty , ++ Cards from Trade Area to Chains or Discard Them
	if (tradeArea.numCards() > 0) {
		std::cout << "Cards in Trade Area: " << tradeArea << std::endl;
		choice = UserChoice({ "Begin Trading", "Done Trading" });
		//START TRADING
		if (choice == 1) {
			std::list<std::string> cardOptions = tradeArea.getUnique();
			for(std::string toTrade: cardOptions) {
				//Note: If you finish trading, the remaining cards will remain in the trade area
				std::cout << "Current Card: " << toTrade << std::endl;
				lineBreak();
				int tradeChoice = UserChoice({ "Take Card", "Discard Card", "Finish Trading" });
				
				Card* card = tradeArea.trade(toTrade);
				if (tradeChoice == 1) {
					bool addStatus = player.addToChain(card);
					//This means we were unable to add a chain
					if (!addStatus) {
						tradeArea+=card;
					}
					//We trade all the cards in the trade area of a given type
					while (tradeArea.legal(card)) {
						player.addToChain(tradeArea.trade(toTrade));
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
		std::cout << "Played " << drawn->getName() << std::endl;
		if (player.addToChain(drawn)) {//Cannot add top card to chains
			std::cout << "Cannot add to existing chains. Which would you like to sell?" << std::endl << player << std::endl;
			choice = UserChoice(player.getChainStrings());
			player += player[choice - 1].sell();
			player.removeChain(choice - 1);
			player.addToChain(drawn);
			lineBreak();
		}
		else {
			std::cout << "Added to existing chain!" << std::endl;
		}
		std::cout << player << std::endl;
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


	while (!table.win(winner)) {
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
