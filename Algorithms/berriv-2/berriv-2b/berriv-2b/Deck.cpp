
//Juan Pablo Bernal and Augusto Rivas
//deck cpp file that implements the functions from the desk header file

//include the header files and libraries
#include "Deck.h"

#include <iostream>
#include <stdlib.h>     
#include <time.h>
using namespace std;

//constructor that creates the deck
Deck::Deck(int x)
{
    size = x; //size
    //set default chars for every suit
    char spades = 's';
    char hearts = 'h';
    char clubs = 'c';
    char diamonds = 'd';
    
    //for loop that runs as many times as the size of the deck and creates a card each run
    for (int x = 1; x <= size; x++)
    {
        //we separate the creation of the cards into four statements to keep track of the suits
        
        //the first 13 cards will be clubs, the next 13 diamonds, and so forth
        if (x < 14) {
            cards.append(x, clubs);
        }
        else if (x > 13 && x < 27) {
            cards.append((x - 13), diamonds);
        }
        else if (x > 26 && x < 40) {
            
            cards.append((x - 26), hearts);
        }
        else if (x > 39) {
            cards.append((x - 39), spades);
        }
    }
    
    
}

Deck::~Deck()
{
	node<Card> *temp;
    while (cards.front != NULL) {
        temp = cards.front;
        cards.front = temp->next;
		delete temp;
    } 
}

/*
 Our algorithm basically consists in splitting the deck in half and grabbing the first node of the first half and pointing it to first node of the second half and then pointing that node to the second of the first half and so forth.
*/
void Deck::shuffle()
{
    //node pointers that we will use for the shuffling
    node<Card> *first = cards.front;
    node<Card> *curr = cards.front;;
    node<Card> *temp= cards.front;
    node<Card> *temp2 = cards.front;
    
    srand(time(NULL)); //set the randomizer
    
    /*
     For loop that shuffles the cards anywhere between 6 and 36 times.
     We found that any number in this range shuffles the deck sufficiently and is also time efficient.
     The rand makes the shuffle output different in every game.
    */
	 
    for (int x = 0; x <= (rand() % 30) + 6; x++) {
        
        //for loop that runs with half the deck
        for (int x = 0; x < size /2; x++) {
            curr = curr->next; //curr now points to the next node of the node it was pointing to
        }
        
        temp2 = curr->next; //temp2 points to the next node of curr
        curr->next = NULL; //next node of curr points to null
        curr = temp2; //curr now points to the node temp2 points to
        
        //while temp and temp2 don't point to null this loop will run
        while (temp != NULL && temp2 != NULL)
        {
            temp = first->next; //temp points to the next node of first
            temp2 = curr->next; //temp2 points to next node of curr
            first->next = curr; //the next node of first points to curr
            curr->next = temp; //the next node of curr points to temp
            first = temp; //first points to the node temp points to
            curr = temp2; //curr points to the node temp2 points to
            
        }
        //finally set everything poiting back to the front for the next shuffle
        curr = cards.front;
        first = cards.front;
        temp = cards.front;
        temp2 = cards.front;
    }
	
    
}

Card Deck::deal()
{
	Card card;
	node<Card> *temp = cards.front;
	card = cards.front->nodeValue;
	cards.front = cards.front->next;
	delete temp;
	size -= 1;
	cards.count -= 1;
	return card;
}

void Deck::replace(Card card)
{
	cards.append(card.getValue(), card.getSuit());
}








//print the deck
ostream& operator<< (ostream& ostr, const Deck& deck)
{
    deck.cards.print();//call the print function 
    return ostr;
}



