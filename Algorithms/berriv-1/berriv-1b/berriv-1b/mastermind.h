//Juan Pablo Bernal & Augusto Rivas
// Header file to declare the Mastermind class

#ifndef MASTERMIND_H
#define MASTERMIND_H
// libraries
#include "response.h"
#include "codes.h"
#include <iostream>

class mastermind
{
public:
	mastermind ();// constructor that uses default values 
	mastermind (const int &x, const int &y);//  constructor that uses values given by the user 
	void PrintSecret( Codes &secret) const;// function that prints the secret code 
	void HumanGuess();// function that gets the guess code from the user 
	response Getresponse(Codes guess, response &resp);// function that chck the incorrect and correct values and prints them 
	bool IsSolved(response resp);// function that checks if the game is over, if not it gives the user how many opportunities he has 
	void PlayGame();// function that initializes the secret code, prints it, gets the guess code and repeates until the game is over

private:
	Codes secret;
	Codes guess;
	int length;
	int range;
	int opt;// opportunities counter 
};
#endif
