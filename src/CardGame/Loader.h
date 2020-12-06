#ifndef LOADER_H
#define LOADER_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <string>
#include "Table.h"

class Loader {
	private:
		const std::string fileName = "SavedState.txt";
		Table table;
	public: 

		/*
		* When a new loader object is created, the state of game should be reloaded from a file
		*/
		Loader(std::string, std::string);

		/*
		* When the loader object calls the desctructor, the state of the game should save
		*/
		~Loader();

		/*
		Returns a built table
		*/
		Table& getTable() { return table; }
};

#endif



