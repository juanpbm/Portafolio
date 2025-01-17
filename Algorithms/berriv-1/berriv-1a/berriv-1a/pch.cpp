// source file corresponding to pre-compiled codes library (pch.h) header

//included libraries 
#include "pch.h"
#include "time.h"

//Constructor: gets the values of the length and range and calls the function
//to generate the secret code 
Codes::Codes(const int &n, const int &m) 
{
	length = n;
	range = m;
}

// Generate the secret code 
void Codes::GenSecretCode()
{
	// set the seed of the rand function to time so evert time the code runs the 
	//random numbers will be differnt 
	srand(time(NULL));
	for (int x = 0; x < length; x++)
	{
		// use the function rand() to generate the code with ramandom numbers
		code.push_back(rand() % range);  
	}
}

// promts the user to enter the guess code 
void Codes::GetGuess()
{
	int error;
	int input;

	cout << "\nEnter your guess only the first " << length 
		<< " values will be taken" << endl;

		do
		{
			error = 0;
			code.clear();
			// make sure that the guess has the same length as the secret code 
			for (int x = 0; x < length; x++)
			{
				// guess the input it can be separated by the spacebar or enter 
				cin >> input;
				//if the input is out of range error changes to 1 and the 
				//program will ask for the imput again 
				if (input < 0 || input >= range) 
				{
					error = 1;
				}
				else {
					code.push_back (input);
				}
			}
			if (error == 1)
				cout << "ERROR !!!!!! \nOne of the values was out of rage"
					"\nTryagain enter all your values" << endl;

		} while (error != 0); //BONUS POINTS check if at least one number in 
		//the guess is out of range 
		
	cout << " Got it !!" << endl;
}

// function to print all the information needed
void Codes::Print(const Codes &guess)
{
	// print the secret code 
	cout << "Secret Code \n"; 
	for (int x = 0; x < length; x++)
	{
		cout << code.at(x) << "  ";
	}
	// print the guess code 
	cout << "\nYour attempted guess \n";
	for (int x = 0; x < length; x++)
	{
		cout << guess.code.at(x) << "  ";
	}
	
	// call and print the functions to check how many numbers are in the 
	//correct and incorrect position
	cout << "\n[" << CheckCorrect(guess) << ", ";
	cout << CheckIncorrect(guess) << "]" << endl;

}

// check how many numbers are equal and in the same position in both codes 
int Codes::CheckCorrect(const Codes &guess)
{
	correct = 0;
	sec.resize(length, 0);
	gue.resize(length, 0);

	for (int x = 0; x < length; x++) 
	{
		if (code.at(x) == guess.code.at(x))
		{
			correct++;
			// change the values to 1 in the vector index of the numbers 
			//found to be equal and in the correct position 
			sec.at(x) = 1;
			gue.at(x) = 1;
		}
	}
	return correct;
}

//check how many numbers are equal but are not in the same position in both codes 
int Codes::CheckIncorrect(const Codes &guess)
{
	incorrect = 0;

	for (int x = 0; x < length; x++)
	{
		for (int i = 0; i < length; i++)
		{
			// check if the numbers are equal, not in the same position
			//and haven't been previously counted
			if (i != x && code.at(x) == guess.code.at(i) && sec.at(x) == 0 && gue.at(i) == 0)
			{
				incorrect++;
				// change the values to 1 in the vector index of the numbers found to be 
				//equal but in the incorrect position 
				sec.at(x) = 1; 
				gue.at(i) = 1;
			}
		}

	}
	// reset the values to 0 of the vectors that check if a number has been counted
	sec.clear(); 
	gue.clear();
	sec.resize(length, 0);
	gue.resize(length, 0);
	return incorrect;
}

//check if the game is over 
int Codes::EndGame()
{
	//if both codes are equal the correct variable will be equal to length 
	if (correct == length) 
	{
		cout << "Congratulations !!! you've won" << endl;
		return 1;
	}
	// if the codes are not equal the opportunities counter will go up and show the user how many left 
	opt++;
	cout << "\nNice try you still have "<< 11 - opt << " oportunities";
	return 0;
}

// guet the opportunities counter 
int Codes::GetOpt() const
{
	return opt;
}
