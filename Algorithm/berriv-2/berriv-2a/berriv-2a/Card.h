//Juan Pablo Bernal and Augusto Rivas
//header file for the card class - where all the functions and variables are declared

#ifndef CARD_H
#define CARD_H

//include libraries
#include <iostream>
using namespace std;
class Card
{
public:
    Card(); //default constructor
    void setValue(int _number); //function that sets the card value
    void setSuit(char _suit); //function that sets the suit value
    int getValue() {return number;}; //function that gets and returns the card value
    char getSuit() {return suit;}; //function that gets and returns the card's suit
    
private:
    int number; //int for the card's value
    char suit; //character for the card's suit
};

ostream& operator<< (ostream& ostr, Card card); //overload operator << used to print a card


#endif
