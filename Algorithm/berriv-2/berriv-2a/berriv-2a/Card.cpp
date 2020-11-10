//Juan Pablo Bernal and Augusto Rivas
//card cpp file that implements the functions from the class header file

//include header file and library
#include "Card.h"
#include <iostream>

using namespace std;
//default constructor setting the number and suit to default values
Card::Card()
{
    number = 0;
    suit = '-';
}
//setting the number of the card
void Card::setValue(int _number){
    number = _number;
}
//setting the suit of the card
void Card::setSuit(char _suit){
    suit = _suit;
}

ostream& operator<< (ostream& ostr, Card card)
{
    //the first four statements check the card number so that we know when we need to convert the number to a letter, along with its suit
    if (card.getValue() == 1)
    {
        ostr << "A" << card.getSuit() << "  ";
    }
    else if (card.getValue() == 11)
    {
        ostr << "J" << card.getSuit() << "  ";
    }
    else if (card.getValue() == 12)
    {
        ostr << "Q" << card.getSuit() << "  ";
    }
    else if (card.getValue() == 13)
    {
        ostr << "K" << card.getSuit() << "  ";
    }
    //else we simply print the card number as it is and its suit
    else {
        ostr << card.getValue() << card.getSuit() << "  ";
    }
    
    return ostr;
}




