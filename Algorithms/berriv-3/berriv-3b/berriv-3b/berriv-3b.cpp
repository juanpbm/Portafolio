/// Juan Pablo Bernal & Augusto Rivas 
// main function to solve a word search puzzle 

// included libraries 
#include "d_matrix.h"
#include "Dictionary.h" 
#include "Grid.h"
#include "Heap.h"
#include <iostream>
#include <fstream>

using namespace std;

// function to scan all the grid for candidate words and thearch them in the dictionary and print if found 
void findMatches(Dictionary dictionary, Grid board);

int main()
{
	string input;// grid file name
	int sorting;// sorting algorithm choice
	cout << "Please enter the name of the file that contains de grid (without .txt): "; // ask the user for the .txt file to open 
	cin >> input;
	input = input + ".txt";// add the .txt at the end of the file 
	Grid board(input);// initialize the grid with the .txt file name gotten from the user 
	board.print();//print the grid 

	Dictionary dictionary("dictionary.txt"); // initialize the dictionary with the .txt file name 
	cout << "\nPlease enter the number of the sorting method:\n1 for Selection Sort\n2 for Quick Sort\n3 for Heap Sort\n";
	cin >> sorting;

	switch (sorting)// sorth the dictionary depending of the users choice
	{
	case 1:

		dictionary.sSort(); // sort the dictionary with selection sort 
		break;
	case 2:

		dictionary.qSort(0, dictionary.size() - 1);// sort the dictionary with quick sort 
		break;
	case 3:

		dictionary.hSort();// sort the dictionary with heap sort 
		break;
	default:
		cout << "\nERROR!!!! Wrong selction method code";// error if the input is wrong 
		return -1;
	}
	// after trying the sorthing algorithms we concluded that the fastest is quick sort then heap sort and finally selection sort 
	cout << dictionary;// print the dictionary 
	findMatches(dictionary, board);// find all the matches in the grid and print them

	return 0;
}


void findMatches(Dictionary dictionary, Grid board)
{
	string candidate; // posible word 
	int row = board.getRow();
	int col = board.getCol();
	matrix<char> grid = board.getGrid();
	int y;//column 0f the char to of the posible word 
	int x;//row of the char to of the posible word 
	int p;// counter to exit loops in diagonal 

	// scan all the grid to find posible words 
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//up
			candidate = grid[i][j];
			x = i - 1; //position for next letter
			do
			{
				if (x < 0) // if its the end of the grid wrap arround the corners 
					x = row - 1;

				candidate += grid[x][j];
				if (candidate.size() > 4) // if the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}
				x--;
				if (i == row - 1 && x == row - 2)//special case at the last char of the grid 
					x++;
			} while (x != i);

			//down
			candidate = grid[i][j];
			x = i; //position for next letter
			do
			{
				if (x == row - 1) // if its the end of the grid wrap arround the corners
					x = -1;
				x++;
				candidate += grid[x][j];
				if (candidate.size() > 4) // if the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}

			} while (x != i);

			//left
			candidate = grid[i][j];
			x = j - 1; //position for next letter
			do
			{
				if (x < 0) // if its the end of the grid wrap arround the corners
					x = col - 1;

				candidate += grid[i][x];
				if (candidate.size() > 4) // of the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}
				x--;
				if (j == row - 1 && x == col - 2)//special case at the last char of the grid 
					x++;
			} while (x != j);

			//right 
			candidate = grid[i][j];
			x = j; //position for next letter
			do
			{
				if (x == col - 1) // if its the end of the grid wrap arround the corners
					x = -1;
				x++;
				candidate += grid[i][x];
				if (candidate.size() > 4) // if the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}

			} while (x != j);


			//D up left
			candidate = grid[i][j];
			//x and y are the positions of the next letter
			x = i - 1;
			y = j - 1;
			p = 0; //counter variable to break the while loop
			do
			{
				if (x < 0 || y < 0)// if its the end of the grid wrap arround the corners
				{
					//difernet posible ends of the grid 
					if (x < 0 && y < 0)
					{
						x = row - 1;
						y = col - 1;
					}
					else if (x < 0)
					{
						x = row - 1;
					}
					else
					{
						y = col - 1;
					}
				}
				p++;

				candidate += grid[x][y];
				if (candidate.size() > 4) // if the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}
				x--;
				y--;

			} while (p != 16); //run the loop 15 times for a cycle of 15 letters

			//D down left
			candidate = grid[i][j];
			//x and y are the positions of the next letter
			x = i + 1;
			y = j - 1;
			p = 0; //counter variable to break the while loop
			do
			{
				if (x < 0 || y < 0)// if its the end of the grid wrap arround the corners
				{
					//difernet posible ends of the grid 
					if (x < 0 && y < 0)
					{
						x = row - 1;
						y = col - 1;
					}
					else if (x < 0)
					{
						x = row - 1;
					}
					else
					{
						y = col - 1;
					}
				}
				if (x == row) {
					x = 0;
				}
				p++;

				candidate += grid[x][y];
				if (candidate.size() > 4)
				{
					if (dictionary.search(candidate)) // if the candidate is more than 4 char long search for the word in the dictionary 
						cout << "\nFound: " << candidate;
				}
				x++;
				y--;

			} while (p != 16); //run the loop 15 times for a cycle of 15 letters

			//D down right
			candidate = grid[i][j];
			//x and y are the positions of the next letter
			x = i + 1;
			y = j + 1;
			p = 0; //counter variable to break the while loop
			do
			{
				if (x < 0 || y < 0)// if its the end of the grid wrap arround the corners
				{
					//different posible ends of the grid 
					if (x < 0 && y < 0)
					{
						x = row - 1;
						y = col - 1;
					}
					else if (x < 0)
					{
						x = row - 1;
					}
					else
					{
						y = col - 1;
					}
				}
				if (x == row && y == row) {
					x = 0;
					y = 0;
				}
				else if (x == row) {
					x = 0;
				}
				else if (y == row) {
					y = 0;
				}
				p++;

				candidate += grid[x][y];
				if (candidate.size() > 4)// if the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}
				x++;
				y++;

			} while (p != 16); //run the loop 15 times for a cycle of 15 letters

			//D up right
			candidate = grid[i][j];
			//x and y are the positions of the next letter
			x = i - 1;
			y = j + 1;
			p = 0; //counter variable to break the while loop
			do
			{
				if (x < 0 || y < 0)// if its the end of the grid wrap arround the corners
				{
					//difernet posible ends of the grid 
					if (x < 0 && y < 0)
					{
						x = row - 1;
						y = col - 1;
					}
					else if (x < 0)
					{
						x = row - 1;
					}
					else
					{
						y = col - 1;
					}
				}
				if (x == row) {
					x = 0;
				}
				else if (y == row) {
					y = 0;
				}
				p++;

				candidate += grid[x][y];
				if (candidate.size() > 4) // of the candidate is more than 4 char long search for the word in the dictionary 
				{
					if (dictionary.search(candidate))
						cout << "\nFound: " << candidate;
				}
				x--;
				y++;

			} while (p != 16); //run the loop 15 times for a cycle of 15 letters
		}
	}
}