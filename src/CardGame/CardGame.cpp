// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include "Hand.h"
#include "Chain.h"
#include "TradeArea.h"
#include "Players.h"
#include "Table.h"
#include <iostream>
#include <map> 
#include <climits>
#include "CardGame.h"

int UserChoice(vector<char*> choices) {
	while (true) {
		int i = 1;
		for (char* const& choice : choices) {
			cout << i << ". " << choice<<endl;
			i++;
		}
		cout << "Please choose an option" << endl;
		string input;
		getline(cin>>ws, input);
		int userChoice = 0;
		try {
			userChoice = stoi(input);
		}
		catch (exception e) {
			cout << "Invalid choice" << endl;
			continue;
		}
		if (userChoice > 0 && userChoice <= choices.size()) {
			return userChoice;
		}
		else {
			cout << "Invalid choice" << endl;
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
		string name1;
		string name2;
		cout << "Enter player name 1" << endl;
		cin >> name1;
		cout << "Enter player name 2" << endl;
		cin >> name2;
		table = Table(name1, name2, cf);
	}
	else {
		table = Table(cin, cf);
	}
	string winner = "NONE";
	while (!table.win(winner)) {
		choice = UserChoice({"Continue", "Save and exit"});
		if (choice == 2) {
			//TODO exit game
			cout << "Save game"<<endl;
			continue;
		}
		for (Players* currPlayer : { table.p1 ,table.p2 }) {
			cout << table << endl;
			cout << currPlayer->getName() << "'s turn" << endl;
			Card* draw;
			draw = table.deck.draw();
			cout << "You drew " << draw->getName()<<endl;
			cout << table.tradeArea.numCards() << endl;
			if (table.tradeArea.numCards() > 0) {
				//TODO Add bean cards from the TradeArea to chains or discard them.
				//If the other player has left cards in the trade area from the previous turn (in Step 5), the player
				//may add these cards to his / her chains or discard them.				choice = UserChoice({ "Take cards","Discard cards" });				if (choice == 1) {					choice = 0;										while (choice != 1) {						UserChoice					}				}				else {				}
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
