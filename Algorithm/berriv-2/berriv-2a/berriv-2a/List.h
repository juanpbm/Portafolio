//Juan Pablo Bernal and Augusto Rivas
//header file for the list class - where all the functions and variables are declared
#ifndef LIST_H
#define LIST_H 

//include header files
#include "node.h"
#include "Card.h"
class List
{
public:
    List(); //default constructor
    node<Card> *front; //front node pointer
    node<Card> *back; //back node pointer
    int count; //counter to represent the number of cards
    
    void append(int num, char sui); //function to append nodes to the linked list
    void print() const; //print the linked list(deck)
};


#endif
