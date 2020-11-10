//Juan Pablo Bernal and Augusto Rivas
//list cpp file that implements all the functions from the list header file

//include header file and library
#include "List.h"
#include<iostream>

using namespace std;

//constructor that sets the variables to their initial values
List::List()
{
    front = NULL;
    back = NULL;
    count = 0;
}

//append nodes to the linked list
void List::append(int num, char sui) {
    
    //create the card object and give it the number and suit
    Card new_card;
    new_card.setValue(num);
    new_card.setSuit(sui);
    
    //only run this for the first node in the list
    if (count == 0) {
        
        node<Card> *new_node = new node<Card>(new_card); //create a new node with the card information
        front = new_node; //the front now points to the new node
        back = new_node; //the back also points to the new node since it's the one and only
        count++; //count increases
    }
    //for the rest of the nodes
    else {
        
        node<Card> *new_node = new node<Card>(new_card); //create a new node with the card information
        
        back->next = new_node; //the node back was pointing to now points to this new node
        back = new_node; //and then back now points the new node
        count++; //count increases
    }
    
}
//print the linked list
void List::print() const
{
    node<Card> *curr = front; //current node pointer that points to the front
    
    //loop that runs as many times as the count's value(number of cards in deck)
    for (int x = 1; x <= count; x++)
    {
        //print the node value of whatever node curr is pointing to
        cout << curr->nodeValue; 
        
        //curr now points to next node of the node it was pointing to
        curr = curr->next;
        
        //put a line break after every 13 cards(where the suit changes)
        if (x % 13 == 0)
            cout << endl;
    }
}


