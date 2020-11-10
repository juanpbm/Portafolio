//Juan Pablo Bernal & Augusto Rivas
// cpp file that implements all the functions from the header file of the board class
#include "board.h"


board::board(int sqSize)
: value(BoardSize + 1, BoardSize + 1)
// Board constructor
{
    //resize the conflict matrices to the board dimentions and set the board to all empty cells
    col.resize(BoardSize + 1, BoardSize + 1);
    row.resize(BoardSize + 1, BoardSize + 1);
    sqr.resize(BoardSize + 1, BoardSize + 1);
    
    clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
            // set all the conflicts to F
            col[i][j] = false;
            row[i][j] = false;
            sqr[i][j] = false;
        }
    rec = 0;// restart the recursive counter 
    totsolve = 0;// restart the variable that keeps track if the board has been solved 
    
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;
    
    clear();
    
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            // If the read char is not Blank and conver the char to an int
            if (ch != '.')
                setCell(i, j, (int)ch - 48);
        }
    }
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    
    return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
    return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

//update conflicts
void board::conflicts(int i, int j, ValueType val, int set)
{
    if (set == -1)//update conflicts to F when resetting
    {
        row[i][val] = false;
        col[j][val] = false;
        sqr[squareNumber(i, j)][val] = false;
    }
    else// update conflicts to T when a number is assigned to a cell
    {
        row[i][val] = true;
        col[j][val] = true;
        sqr[squareNumber(i, j)][val] = true;
    }
}

//adds a value to a cell or resets the cell and updates the conflicts
void board::setCell(int i, int j, ValueType val)
{
    if (val == -1)// if val is -1 the value of the cell will be reset to empty
    {
        conflicts(i, j, value[i][j], -1); //update the conflicts
        value[i][j] = val; //set the current value equal to -1 (empty cell)
    }
    else// if val is any number other than -1 the value of the cell will be set to that value
    {
        conflicts(i, j, val, 1); //update the conflicts
        value[i][j] = val; //set the current value equal to the value passed to the function
    }
}
//prints conflicts for the rows, columns and squares
void board::printConflicts()
{
    cout << "Conflicts\n";
    cout << "Rows\n";
    //print conflicts for the rows
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (row[i][j])
                cout << " T ";
            else
                cout << " F ";
        }
        cout << endl;
    }
    
    cout << "Columns\n";
    //print conflicts for the columns
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (col[i][j])
                cout << " T ";
            else
                cout << " F ";
        }
        cout << endl;
    }
    
    cout << "squares\n";
    //print conflicts for the squares
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (sqr[i][j])
                cout << " T ";
            else
                cout << " F ";
        }
        cout << endl;
    }
}
//check if the board has been solved
bool board::isSolved()
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            //if any cell is still blank, then it has not been solved
            if (isBlank(i, j))
                return false;
        }
    }
    totsolve = 1;
    return true; //otherwise, no cell is blank and has been solved
}
//function that will be called recursively to solve the board
void board::Solve()
{
    rec++; //increase the count for the # of recursive calls
    vector<int> cell; //vector for the cell
    //check if the board has already been solved
    if (isSolved())
    {
        print(); //print the board and do nothing further
    }
    else
    {
        cell = nextEmpCell(); //get the next empty cell in the board with the least number of posible legal options 
        //run a for loop for the 9 digits
        for (int x = 1; x < 10; x++)
        {
            //check if the digit is legal in that cell and if the board is still unsolved
            if (isLegal(cell, x) && totsolve == 0)
            {
                setCell(cell[0], cell[1], x); //set the cell to the x value
                Solve(); //recursion, call solve again
                if(totsolve == 0)
                    setCell(cell[0], cell[1], -1); //reset the board
            }
        }
        
    }
}
//check if the digit can be used in a given cell
bool board::isLegal(vector<int> cell, int val)
{
    //if there are no conflicts return true
    if (!row[cell[0]][val] && !col[cell[1]][val] && !sqr[squareNumber(cell[0], cell[1])][val])
        return true;
    //else return false, not legal
    else
        return false;
}
//look for the next empty cell with the leats number of posible legal options 
vector<int> board::nextEmpCell()
{
    vector<int> cell;
    vector<int> tempcell;
    tempcell.resize(2); //give the tempcell a size of 2
    cell.resize(2); //give the cell a size of 2
    int min = 9;
    int count;
    //loop to run as long as the board size
    for (int i =1; i <= BoardSize; i++)
    {
        //nested loop to run as long as the board size
        for (int j = 1; j <= BoardSize; j++)
        {
            //set the tempcell to be in the location(i,j)
            tempcell[0] = i;
            tempcell[1] = j;
            //check if the current temp cell is blank
            if (isBlank(i, j))
            {
                count = 0;
                //loop that runs all the digits to check how many possibilities are legal in the cell
                for (int x = 1; x < 10; x++)
                {
                    if (isLegal(tempcell, x))
                    {
                        count++;
                    }
                }
                //if the # of possibilities is less than the min, set i and j to be the next empty cell
                if (count < min) {
                    cell[0] = i;
                    cell[1] = j;
                    min = count; //and update the min to be whatever the last count was
                }
            }
        }
    }
    return cell;
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    
    return (getCell(i, j) == Blank);
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i - 1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j - 1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i, j))
                cout << " " << getCell(i, j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}



