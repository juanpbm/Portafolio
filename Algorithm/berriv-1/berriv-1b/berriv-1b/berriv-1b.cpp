//Juan Pablo Bernal & Augusto Rivas  
//Main function of the Mastermind game 
// where the mastermind object is initialized the playgame function is called
// and the values for length and range arre gotten from the user 


#include "codes.h"
#include "mastermind.h"
#include "response.h"
#include <iostream>

int main()
{
	int  m, n;
	char perso;
	
	cout << "Welcome to Mastermind\n";
	
	// prompt the user to se if he wants to use default values or input personalized ones
	cout << "do you wish to create a personalized vector?(y/n)";
	cin >> perso;
	
	if (perso == 'y' || perso == 'Y') 
	{
		//get the length and range values from the user 
		cout << " \n\nPlease enter the length of the vector: ";
		cin >> n;
		cout << "Please enter the max number of the range: ";
		cin >> m;
		// initialize the mastermind object with parameters and call play game function 
		mastermind game(n, m);
		game.PlayGame();
	}
	else {
		// initialize the mastermind object with default values and call play game function 
		mastermind game;
		game.PlayGame();
	}
	

}

