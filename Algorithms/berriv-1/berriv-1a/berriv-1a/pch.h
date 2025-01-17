// library that contains de class codes to play the game mastermind 
#ifndef PCH_H
#define PCH_H
// included libraries 
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

//class definition
class Codes 
{
	public:
		Codes(const int &n, const int &m); //constructor 
		void GetGuess(); // function to ask and get the guess code from the user 
		void Print(const Codes &guess); // function to print the codes and the answer of how many numbers are correct and incorrect 
		int EndGame(); // check if the user won lost and how many oportunities are left 
		int GetOpt() const; //{ return opt; };
		void GenSecretCode();

	private:
		vector<int> code; 
		int	length;
		int range;
		int opt = 1; // opportunities counter 
		int correct;
		int incorrect;
		// functions to check if the numbers in the guess code are in the correct or incorrect position
		int CheckCorrect(const Codes &guess);
		int CheckIncorrect(const Codes &guess);
		// vectors used to only check once if the number is in the correct or incorrect position
		vector<int> sec;   
		vector<int> gue;
};



#endif //PCH_H
