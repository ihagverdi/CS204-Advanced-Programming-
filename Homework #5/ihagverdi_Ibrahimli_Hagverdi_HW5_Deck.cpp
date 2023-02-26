#include "ihagverdi_Ibrahimli_Hagverdi_HW5_Deck.h"
/*
Implementation file for the Deck Class
Written by Hagverdi Ibrahimli in 25/04/2022
Written for CS204 course Homework 5.
Student id: 30014
*/
Deck::Deck() { // default constructor for the Deck object
	deckSize = 0;
	cardPtr = NULL;
}

Deck::Deck(const Deck &deck) { // deep-copy constructor
	deckSize = deck.deckSize;
	cardPtr = new Card [deckSize];
	for(int i = 0; i < deckSize; i++) {
		cardPtr[i] = deck.cardPtr[i];
	}
}

Deck::~Deck() { // destructor for the Deck object
	delete [] cardPtr;
	cardPtr = NULL; // restore cardPtr and deckSize to 0.
	deckSize = 0;
}

string Deck::toString() const {
	ostringstream os;
	for(int i = 0; i < deckSize; i++) {
		os << i+1 << ": " << cardPtr[i].name << " - " << cardPtr[i].energy << endl; // put string to ostream 
	}
	return os.str(); // return os as string
	
}

ostream& operator << (ostream & os, const Deck &deck) {
	os << deck.toString(); 
	return os; // return os.string
}

const Deck& Deck::operator=(const Deck &obj) { // Overloading = operator s.t. it will assign the rhs to lhs and return lhs object
	if(this != &obj) { //guard for not assigning to same element
		delete [] cardPtr; // delete previously allocated memory
		deckSize = obj.deckSize; // adjusting new size of the lhs
		cardPtr = new Card [deckSize];
		for(int i = 0; i < deckSize; i++) {
			cardPtr[i] = obj.cardPtr[i];
		}
	}
	return *this;
}
Deck Deck::operator+(const Card &crd) { // overloading + operator s.t. it will return a new Deck object as a result of addition of the 
										// lhs deck object and rhs card element.
	Deck newDeck;
	newDeck.deckSize = deckSize+1;
	newDeck.cardPtr = new Card[deckSize+1];
	for(int i = 0; i < deckSize; i++) {
		newDeck.cardPtr[i] = cardPtr[i];
	}
	newDeck.cardPtr[deckSize] = crd;
	return newDeck; 
}

Deck Deck::operator+(const Deck &deck2) { // overloading + (2nd.) s.t. it will return a new Deck object as a result of addition of the 
										// lhs and rhs deck objects.
	Deck newDeck;
	newDeck.deckSize = deckSize + deck2.deckSize; // new size for the new deck object
	newDeck.cardPtr = new Card [newDeck.deckSize];
	for(int i = 0; i < deckSize; i++) { // filling half
		newDeck.cardPtr[i] = cardPtr[i];
	}
	for(int i = deckSize, b = 0; i < newDeck.deckSize, b < deck2.deckSize; i++, b++) { //filling the other half
		newDeck.cardPtr[i] = deck2.cardPtr[b];
	}
	return newDeck;
}

int Deck::totalEnergy() const { // helper member func. calculating total energy of the deck object
	int energy_deck = 0;
	for(int i = 0; i < deckSize; i++) {
		energy_deck += cardPtr[i].energy;
	}
	return energy_deck;
}

bool operator==(const Deck &deck1, const Deck &deck2) { //overloading == operator s.t. it will check if the lhs deck object is equal
														// to the rhs deck object in terms of total energy.
	return (deck1.totalEnergy() == deck2.totalEnergy());
}

bool operator < (const Deck &deck1, const Deck &deck2) { //overloading < operator s.t. it will check if the lhs deck object has less energy
														// than the rhs deck object in terms of total energy.
	return(deck1.totalEnergy() < deck2.totalEnergy());
}

bool Deck::operator > (const int& rhs) const { // Helper member func. to chech whether lhs deck has more cards than the rhs deck
	return(deckSize > rhs);
}

bool Deck::cardExist(const Card &card) const { // helper member func. to check if the rhs card element exists in the lhs card deck
	bool status = false;
	int i = 0;
	while(status != true && i < deckSize) {
		if(cardPtr[i].name == card.name && cardPtr[i].energy == card.energy){
			status = true;
		}
		i++;
	}
	return status;
}

 bool operator <= (const Card &crd, const Deck &deck) { // overloading <= operator s.t. it will check if the lhs card element exists in
														// in rhs deck object
	return deck.cardExist(crd);
}

Card& Deck::operator[] (const int &index) const { // overloading [] operator s.t. it will return a card element at the i_th index of the 
													// deck object.
	return cardPtr[index];
}

const Deck& Deck::operator+=(const Deck& rhs) { // overloading += operator s.t. it will increment the lhs deck object by adding rhs deck
													// object to it.
	Deck temp(*this);
	delete [] cardPtr; // deleting the previously allocated memory to let new data in
	deckSize = temp.deckSize + rhs.deckSize;
	cardPtr = new Card [deckSize];
	for(int i = 0; i < temp.deckSize; i++) { // filling first half
		cardPtr[i] = temp.cardPtr[i];
	}
	for(int i = temp.deckSize, b = 0; i < deckSize, b < rhs.deckSize; i++, b++) { //filling the other half
		cardPtr[i] = rhs.cardPtr[b];
	}
	return *this; //returning the deck object on the lhs so that it allows cascaded assign.
}

Deck Deck::operator- (const int &numDel) { // overloading - operator s.t. it will create and return a new deck object with the lhs deck
											// object diminished by the numDel number of card elements.
	Deck newDeck;
	if(numDel >= deckSize) { // if number of deleted cards is more than the deck size
		newDeck.cardPtr = NULL;
		newDeck.deckSize = 0;
		return newDeck;
	}
	else { 
		newDeck.deckSize = deckSize - numDel;
		newDeck.cardPtr = new Card[newDeck.deckSize];
		for(int i = 0, b = numDel; i < newDeck.deckSize, b <deckSize; i ++, b++) { // fill in the deck with remained cards.
			newDeck.cardPtr[i].name = cardPtr[b].name;
			newDeck.cardPtr[i].energy = cardPtr[b].energy;
		}
	}
	return newDeck;
}