//Juan Pablo Bernal and Augusto Rivas
// berriv-2a.cpp : This file contains the 'main' function. Program execution begins and ends there.

//include all the header files and libraries

#include "Card.h"
#include "Deck.h"
#include "List.h"
#include <iostream>

using namespace std;

//main function
int main()
{
    Deck full(52); //create a deck object and pass the size of the deck
    cout << "DECK\n" << endl;
    cout << full; //print the deck with the overloaded operator <<
    cout << "\nSHUFFLED DECK\n" << endl;
    full.shuffle(); //call the shuffle function to shuffle the deck
    cout << full; //print the shuffled deck with the overloaded operator <<
}
