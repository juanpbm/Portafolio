// Juan Pablo Bernal & Augusto Rivas
// Main cpp file where the board class and its classes are being called from
#include <iostream>
#include "board.h"

int main()
{
    ifstream fin;
    board b1(SquareSize);
    int recursive = 0;
    int x = 0;// number of boards in the file 
    // Read the sudoku grids from the file.
    string fileName = "sudoku3-1.txt";
    fin.open(fileName);
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    //while the file keeps reading digits
    while (fin && fin.peek() != 'Z')
    {
        x++;// number of the board 
        cout << "sudoku" << x <<"\n";
        //call the functions to initialize and print the sudoku
        b1.initialize(fin);
        b1.print();
        b1.printConflicts();
        b1.Solve();// call the function to solve the current board
        cout << b1.rec << endl; //print the recursive count
        recursive += b1.rec; //add the recursive count to the total recursive sum
        
    }
    cout << "average : " << recursive / x; //print out the average recursive calls
    fin.close();
    
    return 0;
}
