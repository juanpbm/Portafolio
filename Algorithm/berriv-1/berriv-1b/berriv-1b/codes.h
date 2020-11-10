// library that contains de class codes to play the game mastermind 
#ifndef CODES_H
#define CODES_H
// included libraries 
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

//class definition
class Codes
{
public:
	Codes();
	void defCodes(const int &n, const int &m); //constructor 
	void GetGuess(); // function to ask and get the guess code from the user 
	void Print(); // function to print the codes and the answer of how many numbers are correct and incorrect 
	void GenSecretCode();
	vector<int> GetCode() { return (code); }
	// functions to check if the numbers in the guess code are in the correct or incorrect position
	int CheckCorrect(const Codes &guess);
	int CheckIncorrect(const Codes &guess);

private:
	vector<int> code;
	int	length;
	int range;
	// vectors used to only check once if the number is in the correct or incorrect position
	vector<int> sec;
	vector<int> gue;
};



#endif //PCH_H
