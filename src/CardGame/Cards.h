#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card {
	public:
		virtual int getCardsPerCoin(int coins) = 0;
		virtual string getName() = 0;
		virtual void print(ostream& out) = 0;
};

class Blue : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Chili : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Stink : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Green : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Soy : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Black : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Red : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};

class Garden : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
		void print(ostream& out);
};