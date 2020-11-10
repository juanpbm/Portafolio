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

// selection sort function 
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

// quick sort function 
void Dictionary::qSort(int left, int right)
{
	int s;
	if (left < right)
	{
		s = partition(left, right);
		qSort(left , (s - 1));//sort the left subvector
		qSort((s + 1), right);//sort the right subvector 
	}
}

//function to do the partition of the vector and put all the smaller values on the left of the pivot
int Dictionary::partition(int left, int right) 
{
	string x = dictionary[right];// pivot last element of the vector or subvector 
	int i = left - 1;
	string temp;// temporal variable swap 2 elements 

	for (int j = left; j < right; j++)// scan the vector or subvector to find values that are smaller than te pivot and put them int the left subvector 
	{
		if (dictionary[j] <= x)
		{
			i++; 
			temp = dictionary[i];
			dictionary[i] = dictionary[j];
			dictionary[j] = temp;
		}
	}
	
	// put the pivot at the end of the left subvector 
	temp = dictionary[i + 1];
	dictionary[i + 1] = dictionary[right];
	dictionary[right] = temp; 
	
	return (i + 1);// return the pivot index
}

// call the heap sort function
void Dictionary::hSort()
{
	Heap<string> heap;
	heap.initializeMaxHeap(dictionary);//initialize the heap with the dictionary
	heap.heapSort();//sort the heap
	dictionary = heap.getTree();// asign the heap values back to the dictionary 
	dictionary.erase(dictionary.begin());//remove the first element that in the heap was nothing
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
