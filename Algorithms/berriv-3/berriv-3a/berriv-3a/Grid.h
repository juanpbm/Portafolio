#pragma once  
//Juan Pablo Bernal & Augusto Rivas 
// header file of the grid clas 

//included libraries 
# include "d_matrix.h"
#include <fstream>

class Grid
{
public:
	Grid(string gridname);//// constructor witht the txt file as parameter 
	void print();// function to print all the values in the grid 
	int getRow() { return row; }; 
	int getCol() { return col; }; 
	matrix<char> getGrid() { return grid; }; 

private:
	matrix<char> grid;// matrix to store the characters of the puzzle 
	int row;// number of rows
	int col;// number of columns

};
