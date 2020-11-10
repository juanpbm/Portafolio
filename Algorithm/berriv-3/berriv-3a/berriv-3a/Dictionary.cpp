// Juan Pablo Bernal & Augusto Rivas
// cpp file to declare functions of the dictionary class 
#include "Dictionary.h"

using namespace std;

// constructor 
Dictionary::Dictionary(string filename)
{
	//open and read a txt file with all the words and store it in the dictionary vector 
	ifstream infile;
	infile.open(filename);
	string x;

	if (!infile)
		cout << "Error file not fond" << endl;// in case the file could not be opened print error 
	else {
		while (infile >> x)
		{
			dictionary.push_back(x);
		}
	}

	infile.close(); // close the txt file 
}

// selesction sort function 
void Dictionary::sSort()
{
	string temp; // temporal variale to make the swap 
	int min;// store the index of the min value 
	for (int x = 0; x < dictionary.size(); x++)
	{
		min = x; 
		for (int i = x + 1; i < dictionary.size(); i++) 
		{
			
			if (dictionary[i] < dictionary[min])
			{
				min = i; // modify the min value index 
			}
		
		}

		if (min != x) { // swap the elements if the min is not in the x position
			temp = dictionary[min];
			dictionary[min] = dictionary[x];
			dictionary[x] = temp;
		}
	}
}

void Dictionary::qSort()
{
}

void Dictionary::hSort()
{
}



//use binary search in the sorted dictionary to find candidate words
bool Dictionary::search(string word)
{
	int L = 0;
	int R = dictionary.size() - 1; 
	int m;

	while (L <= R)
	{
		m = floor((L + R) / 2);
		if (dictionary.at(m) < word)
			L = m + 1;
		else if (dictionary.at(m) > word)
			R = m - 1;
		else {
			return true;
		}
	}
		return false;
}

//overloaded operator to print all the values in the dictionary 
ostream& operator<< (ostream& ostr, const Dictionary& dic) 
{

	for (int x = 0; x < dic.dictionary.size(); x++)
	{
		ostr << dic.dictionary[x] << endl;
	}

	return ostr;
}


