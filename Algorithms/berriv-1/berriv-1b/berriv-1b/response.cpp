// Augusto Rivas and Juan Pablo Bernal
//  response.cpp
// This file implements all the functions from the header file

#include "response.h"

response::response(){} //default constructor

//function that sets the response values(correct and incorrect)to the private members of this class
void response::setValues(Codes &secret, Codes &guess){
    
    //call the function that returns the num. of correct values and set it to local variable
    numCorrect = secret.CheckCorrect(guess);
    //call the function that returns the num. of incorrect values and set it to local variable
    numIncorrect = secret.CheckIncorrect(guess);
    
}
//function that returns the number of correct values
int response::getCorrect(){
    return numCorrect;
}
//function that returns the number of incorrect values
int response::getIncorrect(){
    return numIncorrect;
}
//overload operator == used to correctly compare two response objects
bool operator==(const response &lhs, const response &rhs){
    //check if the values from the two objects are equal
    if (lhs.numCorrect == rhs.numCorrect && lhs.numIncorrect == rhs.numIncorrect)
        return true;
    else
        return false;
}
//overload operator << used to correctly print out the members of the class
ostream& operator << (ostream& ostr, const response &response){
    //print the member values of correct and incorrect, respectively
    ostr << "Number of correct: " << response.numCorrect <<endl;
    ostr << "Number of incorrect: " << response.numIncorrect<<endl;
    return ostr;
}

