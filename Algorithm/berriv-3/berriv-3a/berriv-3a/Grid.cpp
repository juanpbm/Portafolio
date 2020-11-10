// Juan Pablo Bernal & Augusto Rivas
// cpp file to declare functions of the grid class

// included libraries 
#include "Grid.h"
#include <fstream>

// constructor 
Grid::Grid(string gridname)
{
	//open the file and read from it the number of rows, columns and the puzzle grid 
	ifstream infile;
	infile.open(gridname);

	if (!infile)
		cout << "Error File not Found\n";// in case the file could not be opened print error 
	else {
		infile >> row;
		infile >> col;
		grid.resize(row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				infile >> grid[i][j];
			}
		}
	}

	infile.close();//close the file 
}

// print the grid 
void Grid::print()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}




