//Augusto Rivas and Juan Pablo Bernal
//this header file contains all the declarations for the maze class
#pragma once 

//include necessary libraries
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h" 

using namespace std;

class maze
{
public:
    maze(ifstream &fin);
    void print(int goalI, int goalJ, int currI, int currJ);
    bool isLegal(int i, int j);
    
    void setMap(int i, int j, int n);
    matrix<int> getMap(int i, int j) const;
    void mapMazeToGraph(graph &g);
    void findPathNonRecursive(graph &g);//find the path with a non recursive approach using BFS
    void findPathRecursive(graph &g, int n, int prev);//find the path recursively with DFS
    vector<int> visited;//visited vector to store the visited nodes
    int getCols();//get the columns
    int getRows();//get the rows
    bool exists;//know when maze has be solved, if the maze have solution or not
    vector<int> path;// store the movements that have to be made to finish the maze (-1 left, 1 right, -2 up, 2 down)
    
private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    
    matrix<bool> value;
    matrix<int> map;      // Mapping from maze (i,j) values to node index values
};



