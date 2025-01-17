// implementation of the Mastermind game

// included libraries 
#include "pch.h"
#include <iostream>
#include <vector>



int main()
{

	cout << "Welcome to Mastermind\n";
	int endgame = 0;
	int m, n;
	//get the length and range values from the user 
	cout << " \n\nPlease enter the length of the vector: ";
	cin >> n;
	cout << "Please enter the max number of the range: ";
	cin >> m;
	// call the codes class constructor 
	Codes secret (n, m);
	secret.GenSecretCode();
	Codes guess(n, m);

	//loop to play the game 10 times or untill the user wins 
	while (endgame == 0 && secret.GetOpt() <= 10) {
		guess.GetGuess();// guet the gess from the user
		secret.Print(guess);// call the print function 
		endgame = secret.EndGame();// see if the game is over or not
	}
	 
	if (endgame == 0)
		cout << "\nSorry you are a loser";
}
