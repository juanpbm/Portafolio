#pragma once

#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>

using namespace std;

typedef int WeightType;
typedef int NodeType;

int const MaxNumNodex = 9999;

typedef int NodeWeight;
typedef int EdgeWeight;

class node
{
   public:
      node();
      node(const node &);
      node &operator=(const node &);
   
      void setId(int i);
      int getId() const;

      void setWeight(NodeWeight);
      NodeWeight getWeight() const;
   
      void setNode(int, NodeWeight, bool, bool);

      void mark();
      void unMark();
      bool isMarked() const;

      void visit();
      void unVisit();
      bool isVisited() const;

   private:
      int id;
      NodeWeight weight;
      bool marked;
      bool visited;
};



class edge
{
   public:
      edge();
      edge(int, int, EdgeWeight = 0);
      edge(const edge &);
      edge &operator=(const edge &);   

      void setWeight(EdgeWeight);
      EdgeWeight getWeight() const; 

      int getSource() const;
      int getDest() const;

      void setValid();
      void setInvalid();
      bool isValid() const;

      void mark();
      void unMark();
      bool isMarked() const;

      void visit();
      void unVisit();
      bool isVisited() const;

      void setEdge(int, int, EdgeWeight);

   private:
      int source;
      int dest;
      EdgeWeight weight;
      bool valid;         // equals true if edge is valid, otherwise the
      bool visited;
      bool marked;
      // edge is invalid
};


class graph
{
  public:
   graph();
   graph(int n);
   graph(ifstream &fin);
   graph(const graph &);
   graph &operator=(const graph &);   

   void addEdge(int i, int j, NodeWeight w = 0);
   void removeEdge(int i, int j);

   int addNode(NodeWeight w = 0);
   int addNode(node n);

   void setEdgeWeight(int i, int j, EdgeWeight w = 0);
   EdgeWeight getEdgeWeight(int i, int j) const;

   NodeWeight getTotalNodeWeight();
   EdgeWeight getTotalEdgeWeight();

   void setNodeWeight(int i, NodeWeight w = 0);
   NodeWeight getNodeWeight(int i) const;

   bool isEdge(NodeType i, NodeType j) const;
   int numNodes() const;
   int numEdges() const;
   
   node &getNode(int);
   const node &getNode(int) const;
   edge &getEdge(int i,int j);
   const edge &getEdge(int i, int j) const;

   void printNodes() const;
   void printEdges() const;

   void mark(int i);
   void mark(int i, int j);
   void unMark(int i);
   void unMark(int i, int j);
   bool isMarked(int i) const;
   bool isMarked(int i, int j) const;
   void clearMark();
   bool allNodesMarked();

   void visit(int i);
   void visit(int i, int j);
   void unVisit(int i);
   void unVisit(int i, int j);
   bool isVisited(int i, int j) const;
   bool isVisited(int i) const;
   void clearVisit();
   bool allNodesVisited();

  private:
   matrix<edge> edges;
   vector<node> nodes;
   int NumEdges;

};


