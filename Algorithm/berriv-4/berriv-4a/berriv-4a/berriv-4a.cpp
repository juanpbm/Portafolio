// Juan Pablo Bernal & Augusto Rivas
// Main cpp file where the board class and its classes are being called from 
#include <iostream>
#include "board.h"

int main()
{
    ifstream fin;
    board b1(SquareSize);
    
    // Read the first sudoku grid from the file.
    string fileName = "sudoku1.txt";
    cout << " Sudoku 1\n";
    fin.open(fileName);
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    //while the file keeps reading digits
    while (fin && fin.peek() != 'Z')
    {
        //call the functions to initialize and print the sudoku
        b1.initialize(fin);
        b1.print();
        b1.printConflicts();
    }
    
    fin.close();
    
    //check if the board is solved
    if (b1.isSolved())
        cout << "The board is solved\n";
    else
        cout << "The board is not solved\n";
    b1.clear();
    
    // Read the second sudoku grid from the file.
    cout << " Sudoku 2\n";
    fileName = "sudoku2.txt";
    fin.open(fileName);
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    //while the file keeps reading digits
    while (fin && fin.peek() != 'Z')
    {
        //call the functions to initialize and print the sudoku
        b1.initialize(fin);
        b1.print();
        b1.printConflicts();
    }
    
    fin.close();
    //check if the board is solved
    if (b1.isSolved())
        cout << "The board is solved\n";
    else
        cout << "The board is not solved\n";
    b1.clear();
    
    // Read the third sudoku grid from the file.
    cout << " Sudoku 3\n";
    fileName = "sudoku3.txt";
    fin.open(fileName);
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    //while the file keeps reading digits
    while (fin && fin.peek() != 'Z')
    {
        //call the functions to initialize and print the sudoku
        b1.initialize(fin);
        b1.print();
        b1.printConflicts();
    }
    fin.close();
    //check if the board is solved
    if (b1.isSolved())
        cout << "The board is solved\n";
    else
        cout << "The board is not solved\n";
    
    return 0;
}

