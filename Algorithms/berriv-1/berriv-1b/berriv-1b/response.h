// Augusto Rivas and Juan Pablo Bernal
//  response.hpp
// This header files declares all the functions and variables that will be used later in the response.cpp file

#ifndef RESPONSE_H
#define RESPONSE_H

#include "codes.h" //include the codes header file to use the code class
#include <iostream>
using namespace std;

class response
{
//declaration of the public members
public:
    response(); //constructor
    //function that sets the response values(correct and incorrect)to the private members of this class
    void setValues(Codes &secret, Codes &guess);
    //function that returns the number of correct values
    int getCorrect();
    //function that returns the number of incorrect values
    int getIncorrect();
    //overload operator == used to correctly compare two response objects
    friend bool operator == (const response &lhs, const response &rhs);
    //overload operator << used to correctly print out the members of the class
    friend ostream& operator << (ostream& ostr, const response &response);
private:
    int numCorrect; //variable to hold the number correct values
    int numIncorrect;//variable to hold the number of incorrect values
};

#endif
