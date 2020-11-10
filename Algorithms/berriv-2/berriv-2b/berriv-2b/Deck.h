//Juan Pablo Bernal and Augusto Rivas
//header file for the deck class - where all the functions and variables are declared
#ifndef DECK_H
#define DECK_H

//include header files
#include "Card.h"
#include "node.h"
#include "List.h"

class Deck
{
public:
    Deck(int size);//constructor that takes in the size of the deck and creates it
	Deck() {}; 
	    ~Deck();
    void shuffle();//function to shuffle the cards
    List cards;//creat list object - where the linked lists reside
	Card deal();
	void replace(Card card);


private:
    int size; //size of the deck
};

ostream& operator<< (ostream& ostr, const Deck& deck); //overload operator << for printing the deck

#endif
