//Augusto Rivas and Juan Pablo Bernal
//main file that calls the necessary functions to run the entire program

//include the necessary libraries
#include <iostream>
#include "maze.h"
#include "graph.h"
#include <fstream>

using namespace std;

//main function
int main()
{
    //for loop to input the different mazes
    for(int i = 0; i < 3; i++)
    {
        //variables for the input and default values
        ifstream fin;
        graph g;
        int currcol = 0;
        int currrow = 0;
        string fileName;
        
        //read the corresponding maze
        if (i == 0)
        {
            // Read the maze from the file.
            fileName = "maze1.txt";
            fin.open(fileName.c_str());
            if (!fin)
            {
                cerr << "Cannot open " << fileName << endl;
                exit(1);
            }
        }
        if (i == 1)
        {
            // Read the maze from the file.
            fileName = "maze2.txt";
            fin.open(fileName.c_str());
            if (!fin)
            {
                cerr << "Cannot open " << fileName << endl;
                exit(1);
            }
        }
        if (i == 2)
        {
            // Read the maze from the file.
            fileName = "maze3.txt";
            fin.open(fileName.c_str());
            if (!fin)
            {
                cerr << "Cannot open " << fileName << endl;
                exit(1);
            }
        }
        //while we haven't reached the end of the maze
        while (fin && fin.peek() != 'Z')
        {
            maze m(fin);//start the maze
            m.mapMazeToGraph(g);//map the maze to a graph
            cout << "BFS Algorithm\n";
            m.findPathNonRecursive(g);//call the function to find the path using non recursive DFS
            
            //if the maze exists
            if (m.exists)
            {
                //for loop that runs the length of the maze
                for (int j = 0; j < m.path.size(); j++)
                {
                    //swich where each case represents a movement: L, R, U, D
                    switch (m.path[j])
                    {
                        //move left
                        case -1:
                            currcol -= 1;
                            //print the updated maze
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        //move right
                        case 1:
                            currcol += 1;
                            //print the updated maze
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        //move up
                        case -2:
                            currrow -= 1;
                            //print the updated maze
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        //move down
                        case 2:
                            currrow += 1;
                            //print the updated maze
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        default:
                            cout << "error";
                        break;
                    }
                }
                cout << "\nEnd of the Maze\n";
            }
            
            //from this point on we repeat the same process, but we find the path recursively with DFS
            m.exists = false;
            m.path.clear();
            g.clearVisit();
            int currcol = 0;
            int currrow = 0;
        
            cout << "\nDFS Algorithm\n";
            m.visited.push_back(0);
            g.visit(0);
        
            m.findPathRecursive(g, 0, 0);
        
            if (m.exists)
            {
                for (int j = 0; j < m.path.size(); j++)
                {
                    switch (m.path[j])
                    {
                        case -1:
                            currcol -= 1;
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        case 1:
                            currcol += 1;
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        case -2:
                            currrow -= 1;
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        case 2:
                            currrow += 1;
                            m.print(m.getRows() - 1, m.getCols() - 1, currrow, currcol);
                            break;
                        default:
                            cout << "error";
                            break;
                    }
                }
                cout << "\nEnd of the Maze\n";
            }
        }
        fin.close();//close the file
    }
}
