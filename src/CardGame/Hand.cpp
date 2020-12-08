#include "Hand.h"
#include <fstream>
#include <cstdio>


void Hand::display(std::ostream& os) {
	std::vector<std::string> strs = getStrings();
	for (std::string s : strs) {
		os << s << " ";
	}
}

std::ostream& operator<< (std::ostream& os, Hand& hand) {
	hand.display(os);
	return os;
}

std::vector<std::string> Hand::getStrings()
{
	std::vector<std::string> strs;
	for (int i = 0; i < queue.size(); i++) {
		Card* currTop = top();
		strs.push_back(currTop->getName());
		queue.pop();
		queue.push(currTop);
	}
	return strs;
}
bool comparePtrToCardH(Card* a, Card* b) { return (*a > *b); }
/*
Pushes a card to the back of the queue
*/
Hand& Hand::operator+= (Card* card) {
	if (card == nullptr) {
		return *(this);
	}
	std::vector<Card*> vec;
	while (!queue.empty()) {
		vec.push_back(queue.front());
		queue.pop();
	}
	vec.push_back(card);
	std::sort(vec.begin(), vec.end(), comparePtrToCardH);
	while (!vec.empty()) {
		queue.push(vec.back());
		vec.pop_back();
	}
	return *(this);
}


/*
Returns and removes a Card from a given index.
If the index is invalid, return a nullptr.
*/
Card* Hand::operator[] (int index) {
	if (index < 0 || index >= queue.size()) {
		return nullptr;
	}
	std::list<Card*> lst;
	Card * ret = nullptr;
	int i = 0;
	while (!queue.empty()) {
		lst.push_back(queue.front());
		if (i == index) {
			ret = queue.front();
		}
		i++;
		queue.pop();
	}
	i = 0;
	while (!lst.empty()) {
		if (i != index){
			queue.push(lst.front());
		}
		i++;
		lst.pop_front();
	}
	return ret;
}

/*
Returns and removes the top card from the player's hand
*/
Card* Hand::play() {
	if (queue.empty()) {
		return nullptr;
	}
	Card* topCard = top();
	queue.pop();
	return topCard;
}

/*
Returns but does not remove the top card from the player's hand
*/
Card* Hand::top() const {
	if (queue.empty()) {
		return nullptr;
	}
	return queue.front();
}
