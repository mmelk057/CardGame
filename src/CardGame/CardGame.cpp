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
			std::cout << "Invalid choice" << std::endl;
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
	//Testing
	CardFactory* cf = CardFactory::getFactory();
	int choice = UserChoice({ "New game", "Load game from file" });
	Table table;
	if (choice == 1) {
		std::string name1,name2;
		std::cout << "Enter player name 1" << std::endl;
		std::cin >> name1;
		std::cout << "Enter player name 2" << std::endl;
		std::cin >> name2;
		table = Table(name1, name2, cf);
	}
	else {
		table = Table(std::cin, cf);
	}
	std::string winner = "NONE";
	while (!table.win(winner)) {
		choice = UserChoice({"Continue", "Save and exit"});
		if (choice == 2) {
			//TODO exit game
			std::cout << "Save game"<< std::endl;
			continue;
		}
		for (Player currPlayer : { table.getPlayerOne() , table.getPlayerTwo() }) {
			std::cout << table << std::endl;
			std::cout << currPlayer.getName() << "'s turn" << std::endl;
			Card* draw = table.getDeck().draw();
			std::cout << "You drew " << draw->getName() << std::endl;
			std::cout << table.getTradeArea().numCards() << std::endl;
			if (table.getTradeArea().numCards() > 0) {
				//TODO Add bean cards from the TradeArea to chains or discard them.
				//If the other player has left cards in the trade area from the previous turn (in Step 5), the player
				//may add these cards to his / her chains or discard them.
				choice = UserChoice({ "Take cards","Discard cards" });
				if (choice == 1) {
					choice = 0;
					
					//while (choice != 1) {
					//	UserChoice
					//}
				}
				else {

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
