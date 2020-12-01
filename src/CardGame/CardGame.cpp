// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "CardFactory.h"
#include <iostream>
#include <map> 
#include <climits>


int main()
{
	std::cout << CardFactory::getFactory() << std::endl;
	std::cout << CardFactory::getFactory();
	return 1;
}
