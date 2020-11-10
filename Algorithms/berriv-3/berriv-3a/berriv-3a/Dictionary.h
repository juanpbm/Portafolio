#pragma once
// Juan PAblo Bernal & Augusto Rivas 
// header file of the dictionary class 

// included libraries 
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Dictionary
{
public:
	Dictionary(string filename);// constructor witht the txt file as parameter 
	friend ostream& operator<< (ostream& ostr, const Dictionary& dic);// friend overloaded << operator to print the words in the dictionary 
	void sSort();// sorts the dictionary alphabeticaly using selection sort
	void qSort();// sorts the dictionary alphabeticaly using quick sort
	void hSort();// sorts the dictionary alphabeticaly using heap sort
	bool search(string word);// uses binary search to find words in the dictionary 

private:
	vector<string> dictionary;//vector to store all the words 

};


