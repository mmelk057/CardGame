// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include <iostream>
#include <map> 
#include <climits>


int main()
{
	CardFactory* cf = CardFactory::getFactory();
	delete cf;
	return 1;
}
