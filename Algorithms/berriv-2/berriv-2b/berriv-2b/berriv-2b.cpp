//Juan Pablo Bernal and Augusto Rivas
// berriv-2a.cpp : This file contains the 'main' function. Program execution begins and ends there.

//include all the header files and libraries

#include "Deck.h"
#include "List.h"
#include "Card.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

//main function
int main()
{
    Deck full(52); // create a deck object and pass the size of the deck
    Deck playing; // new deck to store the 24 playing cards
    node<Card> *curr;
    int used[24] = { 0 };// array to keep track of the cards that have been used
    int count = 0;
    char keepPlaying = 'y';
    int selection;
    float points = 0;
    List hand;
    
    cout << "DECK\n\n";
    cout << full; //print the deck with the overloaded operator <<
    cout << "\nSHUFFLED DECK\n\n";
    full.shuffle(); //call the shuffle function to shuffle the deck
    cout << full; //print the shuffled deck with the overloaded operator <<
    
    //for loop to get and asign the 24 cards to the playing deck
    for (int x = 0; x < 24; x++)
    {
        playing.replace(full.deal());
    }
    
    cout << "\nplaying cards\n\n";
    cout << playing;//print the 24 cards deck with the overloaded operator <<
    cout << "\n\nfull deck\n\n";
    cout << full << endl;//print the remaining cards deck with the overloaded operator <<
    curr = playing.cards.front; //current card is the first card of the new deck
    //print instructions
    cout <<	"			HOW TO PLAY\n\
    1. Enter a number from 1 to 24 to select the card in that position\n\
    2. Your point will be calculated:\n\
    (a)receives 10 points for an ace\n\
    (b)receives 5 points for a king queen or jack,\n\
    (c)receives 0 points for an 8, 9 or 10\n\
    (d)loses half of the points for a 7\n\
    (e)loses all of the points for a 2, 3, 4, 5 or 6\n\
    (f)receives 1 point extra, in addition to the above, for a heart.\n\
    3. Decide if you wanna keep playing\n\
    4. The goal is to end the game with the most points.";
    
    //while loop to keep playing the game while there are still cards and the user says yes
    while (count < 24 && keepPlaying == 'y')
    {
        //this do while loop runs until the user enters a card that's not repeated or inside the range
        do {
            cout << "\nEnter your selection [1 to 24]:  ";
            cin >> selection;
            selection -= 1; //this will be used for the index of an array to check for repeated cards
            
            //if the card is repeated or selection is out of range
            if (used[selection] == 1 || selection >= 24 || selection < 0)
            {
                cout << "\nSorry that card has already been selected or the number was out of ranage\n Try Again\n";
            }
        } while (used[selection] == 1 || selection >= 24 || selection < 0);
        
        used [selection] = 1;
        
        //loop to get to the card of the desired location
        for (int x = 0; x < selection; x++)
        {
            curr = curr->next;
        }
        //this is a hand linked list used for storing the cards the player has chosen thus far
        hand.append(curr->nodeValue.getValue(), curr->nodeValue.getSuit());
        
        cout << "\nThe selected card is: " << curr->nodeValue << endl; //print selected card
        
        //these are a series of statements that check the value of the card for calculating the points
        if (hand.back->nodeValue.getValue() == 1)
        {
            cout << "Congratulations you got 10 points\n";
            points += 10;
        }
        else if (hand.back->nodeValue.getValue() >= 11 && hand.back->nodeValue.getValue() <= 13)
        {
            cout << "Congratulations you got 5 points\n";
            points += 5;
        }
        else if (hand.back->nodeValue.getValue() >= 8 && hand.back->nodeValue.getValue() <= 10)
        {
            cout << "You got 0 points\n";
        }
        else if (hand.back->nodeValue.getValue() == 7)
        {
            cout << "Shame you lost half your points points\n";
            points /= 2.0;
        }
        else
        {
            cout << "Shame you lost all your points\n";
            points = 0;
        }
        if (hand.back->nodeValue.getSuit() == 'h')
        {
            cout << "Congratulations you got 1 extra point\n";
			points += 1;
        }
        
        //print the playre's cards
        cout << "\n\nThe cards that you have selected so far are:\n";
        hand.print();
        //print the points
        cout << "You have " << points << " points so far\n";
        
        //this do while loop runs until the user enters y or n to keep playing
		if (count < 24) {
			do
			{
				cout << "\n\nDo you wanna keep playing ? [y / n]: ";
				cin >> keepPlaying;
				keepPlaying = tolower(keepPlaying);
			} while (keepPlaying != 'y' && keepPlaying != 'n');
		}
		else {
			cout << "\nThere are no more cards\n";
		}

		curr = playing.cards.front;
        count++;
    }
    //when the game ends or is ended
    cout << "GAME OVER!!! your final score is: " << points << "\nThanks for playing";
}
