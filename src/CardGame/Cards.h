#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card {
	public:
		friend ostream& operator << (ostream& os, const Card& c);
		virtual int getCardsPerCoin(int coins) = 0;
		virtual string getName() = 0;
	protected:
		virtual void print(ostream& out) const  = 0;
};

class Blue : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Chili : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Stink : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Green : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Soy : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Black : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Red : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};

class Garden : public virtual Card {
	public:
		int getCardsPerCoin(int coins);
		string getName();
	protected:
		void print(ostream& out) const;
};