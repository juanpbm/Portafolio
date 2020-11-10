
//Augusto Rivas and Juan Pablo Bernal
//this file implements all the functions for the maze class

//include necessary libraries
#include "maze.h"
#include <queue>

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;
    
    char x;
    
    value.resize(rows, cols);
    for (int i = 0; i <= rows - 1; i++)
        for (int j = 0; j <= cols - 1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    
    map.resize(rows, cols);
}

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
    map[i][j] = n;
}

matrix<int> maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
    return map;
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;
    
    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");
    
    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");
    
    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    
    return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
    node n;
    edge e;
    int count = 0;
    for (int i = 0; i <= rows - 1; i++)// scan the maze for the legal spaces and get the nodes
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (value[i][j])
            {
                n.setId(count);
                g.addNode(n);
                setMap(i, j, count);
            }
            else {
                setMap(i, j, -1);
            }
            count++;
        }
    }
    
    count = 0;
    int n1, n2;
    
    for (int i = 0; i <= rows - 1; i++)// check the posible edges from each node
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (value[i][j])
            {
                for (int x = 0; x < g.numNodes(); x++)
                {
                    if (count == g.getNode(x).getId())
                        n1 = x;
                }
                if (i - 1 > -1)
                {
                    if (map[i - 1][j] != -1)
                    {
                        for (int x = 0; x < g.numNodes(); x++)
                        {
                            if (map[i - 1][j] == g.getNode(x).getId())
                                n2 = x;
                        }
                        g.addEdge(n1, n2);
                    }
                }
                
                if (i + 1 < rows)
                {
                    if (map[i + 1][j] != -1)
                    {
                        for (int x = 0; x < g.numNodes(); x++)
                        {
                            if (map[i + 1][j] == g.getNode(x).getId())
                                n2 = x;
                        }
                        g.addEdge(n1, n2);
                    }
                }
                
                if (j - 1 > -1)
                {
                    if (map[i][j - 1] != -1)
                    {
                        for (int x = 0; x < g.numNodes(); x++)
                        {
                            if (map[i][j - 1] == g.getNode(x).getId())
                                n2 = x;
                        }
                        g.addEdge(n1, n2);
                    }
                }
                
                if (j + 1 > cols)
                {
                    if (map[i][j + 1] != -1)
                    {
                        for (int x = 0; x < g.numNodes(); x++)
                        {
                            if (map[i + 1][j] == g.getNode(x).getId())
                                n2 = x;
                        }
                        g.addEdge(n1, n2);
                    }
                }
            }
            count++;
        }
    }
}

//function to the find the path recursively using DFS
void maze::findPathRecursive(graph &g, int n, int prev)
{
    //rows and columns of the nodes
    int r1, c1, r2, c2;
    c1 = g.getNode(prev).getId() % getCols();
    r1 = (g.getNode(prev).getId() - c1) / getCols();
    c2 = g.getNode(n).getId() % getCols();
    r2 = (g.getNode(n).getId() - c2) / getCols();
    
    // printout the next move and update the path information
    if (c1 != c2 && !exists)
    {
        if (c1 > c2)
        {
            cout << "Go Left\n";
            path.push_back(-1);
        }
        else
        {
            cout << "Go Right\n";
            path.push_back(1);
        }
    }
    else if (r1 != r2 && !exists)
    {
        if (r1 > r2)
        {
            cout << "Go Up\n";
            path.push_back(-2);
        }
        else {
            cout << "Go Down\n";
            path.push_back(2);
        }
    }
    
    // if the final node is found stop
    if (n == g.numNodes() - 1)
    {
        cout << "\nDFS There is a path to solve the maze\n";
        exists = true;
    }
    else{
        {
            for (int i = 0; i < g.numNodes(); i++)// scan all the nodes
            {
                // if the edge is posible between 2 nodes
                if ((g.isEdge(n, i) || g.isEdge(i, n)) && !g.isVisited(i))
                {
                    visited.push_back(i);// add to visited
                    g.visit(i);
                    findPathRecursive(g, i, n);// recall the function with the new node
                    c1 = g.getNode(i).getId() % getCols();
                    r1 = (g.getNode(i).getId() - c1) / getCols();
                    c2 = g.getNode(n).getId() % getCols();
                    r2 = (g.getNode(n).getId() - c2) / getCols();
                    
                    // if the node has to be revisited printout the move and update the path information
                    if (c1 != c2 && !exists)
                    {
                        if (c1 > c2)
                        {
                            cout << "Go Left\n";
                            path.push_back(-1);
                        }
                        else
                        {
                            cout << "Go Right\n";
                            path.push_back(1);
                        }
                    }
                    else if (r1 != r2 && !exists)
                    {
                        if (r1 > r2) {
                            cout << "Go Up\n";
                            path.push_back(-2);
                        }
                        else{
                            cout << "Go Down\n";
                            path.push_back(2);
                        } 
                    }
                }
            }
        }
    }
}

/*
 --------------BONUS--------------
 We combined the non recursive function for part A with the shortest path search in one function
 */

//function that finds the path in a non recursive manner using BFS and also find the shortest path
void maze::findPathNonRecursive(graph &g)
{
    //initialize variables
    g.clearVisit();
    queue<int> q;
    vector<int> visit;
    vector<int> parents;
    vector<int> p;
    int curr;
    int c1, r1, c2, r2;
    
    //give initial values
    q.push(0);
    visit.push_back(0);
    g.visit(0);
    parents.resize(g.numNodes());
    
    //while the queue is not empty
    while (!q.empty())
    {
        //run the number of nodes
        for (int j = 0; j < g.numNodes(); j++)
        {
            //if an edge exists between the front of the queue and the current j value
            if (g.isEdge(q.front(), j) || g.isEdge(j, q.front()))
            {
                //if the node j is not visited
                if (!g.isVisited(j))
                {
                    q.push(j);//push j into the queue
                    visit.push_back(j); //push j into the visit vector
                    g.visit(j); //mark j as visited in the graph
                    parents[j] = q.front(); //the parent at index j becomes the front of the queue
                }
            }
        }
        q.pop();
    }
    //run the size of the visit vector
    for (int j = 0; j < visit.size(); j++)
    {
        //if the j visited node is the last node
        if (visit[j] == g.numNodes() - 1)
        {
            exists = true;
            curr = j;
        }
    }
    //if a path exists
    if (exists)
    {
        do
        {
            p.push_back(curr);
            curr = parents[curr];
            
        } while (curr != 0);
        p.push_back(0);
        
        //run until j goes from the size of p-1 to 0
        for (int j = p.size() - 1 ; j > 0; j--)
        {
            //calculate the columns and rows
            c1 = g.getNode(p[j]).getId() % getCols();
            r1 = (g.getNode(p[j]).getId() - c1) / getCols();
            c2 = g.getNode(p[j - 1]).getId() % getCols();
            r2 = (g.getNode(p[j - 1]).getId() - c2) / getCols();
            
            // printout the next move and update the path information
            if (c1 != c2)
            {
                if (c1 > c2)
                {
                    cout << "Go Left\n";
                    path.push_back(-1);
                }
                else
                {
                    cout << "Go Right\n";
                    path.push_back(1);
                }
            }
            else if (r1 != r2)
            {
                if (r1 > r2)
                {
                    cout << "Go Up\n";
                    path.push_back(-2);
                }
                else {
                    cout << "Go Down\n";
                    path.push_back(2);
                }
            }
        }
        
        cout << "\nBFS There is a path to solve the maze\n";
        cout<< "BONUS: This is the shortest path as well.\n\n";
    }
}
//return the number of columns
int maze::getCols()
{
    return cols;
}
//return the number of rows
int maze::getRows()
{
    return rows;
}

