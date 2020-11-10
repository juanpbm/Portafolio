//Juan Pablo Bernal & Augusto Rivas 
//cpp file that contains the functions of the mastermind class 

#include "codes.h"
#include "response.h"
#include "mastermind.h"
#include <iostream>

// constructor that uses default values 
mastermind::mastermind()
{
	length = 5;
	range = 10;
	//initialize the length and range values of the code object 
	secret.defCodes(length, range);
	guess.defCodes(length, range);
}

//  constructor that uses values given by the user
mastermind::mastermind(const int & n, const int & m)
{
	length = n;
	range = m;
	//initialize the length and range values of the code object 
	secret.defCodes(n, m);
	guess.defCodes(n, m);
}

// function that prints the secret code
void mastermind::PrintSecret(Codes &secret) const
{
	 secret.Print();
}

// function that gets the guess code from the user
void mastermind::HumanGuess()
{
	guess.GetGuess();
}

// function that chck the incorrect and correct values and prints them 
response mastermind::Getresponse(Codes guess, response &resp)
{
	// set the values of correct and Incorrect 
	resp.setValues(secret, guess);
	cout << "\n[" << resp.getCorrect () << ", ";
	cout << resp.getIncorrect() << "]\n";
	return response();
}

// function that checks if the game is over, if not it gives the user how many opportunities he has 
bool mastermind::IsSolved(response resp)
{
	//if the correct values is the same as the legth of the vector the game is over 
	if ( resp.getCorrect() == length)
	{
		cout << "Congratulations !!! you've won" << endl;
		return false;
	}
	else if (opt < 10) 
	{ 
		cout << "\nNice try you still have " << 10 - opt << " oportunities";
		return true;
	}
}


// function that initializes the secret code, prints it, gets the guess code and repeates until the game is overvoid mastermind::PlayGame()
void mastermind::PlayGame()
{
	//initialize the reponse object 
	response resp;
	secret.GenSecretCode();
	
	//lopp to keep playing the game untill the user wins or he runs out of opportunities 
	do {
		HumanGuess();
		PrintSecret(secret);
		Getresponse(guess, resp);
		opt++;
	} while (IsSolved(resp) && opt < 10);
	
	//if the loop ended because of the user lost disply a game over message  
	if (opt == 10)
		cout << " GAME OVER!!!!!!!!!!! You've lost";
}

