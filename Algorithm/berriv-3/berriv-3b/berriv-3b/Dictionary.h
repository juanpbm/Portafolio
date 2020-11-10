#pragma once
// Juan PAblo Bernal & Augusto Rivas 
// header file of the dictionary class 

// included libraries 
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Heap.h"

using namespace std;

class Dictionary
{
public:
	Dictionary(string filename);// constructor witht the txt file as parameter 
	friend ostream& operator<< (ostream& ostr, const Dictionary& dic);// friend overloaded << operator to print the words in the dictionary 
	void sSort();// sorts the dictionary alphabeticaly using selection sort
	void qSort(int left, int right);//quick sort function
	void hSort();//heap sort function
	bool search(string word);// uses binary search to find words in the dictionary 
	int size() { return dictionary.size(); };//size of the dictionary 
	
private:
	
	vector<string> dictionary;//vector to store all the words 
	int partition(int left, int right);//function to do the partition of the vector and put all the smaller values on the left of the pivot

};