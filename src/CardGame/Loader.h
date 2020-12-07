#ifndef LOADER_H
#define LOADER_H

#ifdef _MSC_VER
#pragma once
#endif _MSC_VER

#include <iostream>
#include <string>
#include "Table.h"

class Player;

class Loader {
	private:
		void savePlayerState(std::ostream&, const Player&);
		const std::string fileName = "SavedState.txt";
		Table table;
	public: 
		Loader() = default;
		~Loader() = default;


		/*
		* Saves the managed Table's state
		*/
		void saveState();

		/*
		* Loads a Table's state
		*/
		void loadState();
		void loadState(std::string, std::string);

		/*
		Returns a built table
		*/
		Table& getTable() { return table; }
};

#endif



