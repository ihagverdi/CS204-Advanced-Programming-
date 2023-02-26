#ifndef _IHAGVERDI_IBRAHIMLI_HAGVERDI_HW5_DECK_H
#define _IHAGVERDI_IBRAHIMLI_HAGVERDI_HW5_DECK_H
/*
Deck class using the Card struct for the card game. 
Written by Hagverdi Ibrahimli in 26/04/2022 
Written for CS204 course Homework5.
Student id: 30014
*/
#include <string>
#include <sstream>
using namespace std;

struct Card{
	string name;
	int energy;
};

class Deck{
public:
	Deck(); //default constructor
	Deck(const Deck &obj); //deep copy constructor
	~Deck(); //destructor
	string toString() const;
	Deck operator+(const Card &crd);
	Deck operator+(const Deck &deck2);
	const Deck& operator=(const Deck &obj);
	int totalEnergy() const;
	bool operator > (const int& rhs) const;
	bool cardExist(const Card &crd) const;
	Card& operator[] (const int &index) const;
	const Deck & operator+=(const Deck& rhs);
	Deck operator- (const int &numElemDelete);
private:
	Card* cardPtr; //pointer to the deck
	int deckSize; //number of cards in deck
};

ostream& operator << (ostream & os, const Deck &deck);
bool operator==(const Deck &deck1, const Deck &deck2);
bool operator < (const Deck &deck1, const Deck &deck2);
bool operator <= (const Card &crd, const Deck &deck);
#endif