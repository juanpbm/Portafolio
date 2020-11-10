#pragma once
// Juan Pablo Bernal & Augusto Rivas 
//header file that declares all the functions and variables for the board class
//include the necessary libraries
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;//  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

class board
// Stores the entire Sudoku board
{
public:
    board(int);
    void clear();
    void initialize(ifstream &fin);
    void print();
    bool isBlank(int, int);
    ValueType getCell(int, int);
    void conflicts(int i, int j, ValueType val, int set);
    void setCell(int i, int j, ValueType val);
    void printConflicts();
    bool isSolved();
    
private:
    
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    
    matrix<ValueType> value;
	// conflict matrices 
    matrix<bool> col;//columns
    matrix<bool> row;//rows
    matrix<bool> sqr;//squares 
};
