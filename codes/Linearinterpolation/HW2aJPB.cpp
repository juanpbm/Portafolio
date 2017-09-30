// made by Juan Pablo Bernal
// this program will use linearinterpolation to predict the value of the lift coefficient that the user wants 
//libraries
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;
#define MAXIT 100 
//sub function prototype
int ordered(double fpa[], int num_pts);
int check (double fpa[],double x,int i);
double interp (double fpa[], double col[], int i, double pth);
int main (void){

	double pth;
	int i=0,k,x;
	ifstream infile;
	infile.open("fpa_col.txt");// read from file 
	double fpa[MAXIT],col[MAXIT];
	while (infile>>fpa[i]>>col[i]){
		i++;
    }
	for (int K=0; K<i; K++){//show data 
		cout << fpa[K] << "    "<< col[K] <<endl;
	}
     
    if (ordered(fpa,i)==0){// check if the data in in order 
    	cout << "ERROR!!! the file is not in order";
	}else{
		do {//prompt the user and get value 
		cout << "please enter the Flight Path Angle (degrees) from "<<fpa[0] <<" to "<<fpa[i-1]<<" --->";
		cin >> pth;
	    }while (check (fpa,pth,i)==0);
	
	cout << "The Coefficient for a Flight Path Angle of "<<pth<<"° is :  "<<interp ( fpa , col, i, pth);
	
	
	}     
return 0;
}

int ordered(double fpa[], int num_pts){
	 int i;
	 for (i=0;i<num_pts-1;i++){// check if the data is in order 
	 	if (fpa[i]>fpa[i+1])
	 	return 0;
	 	
	 }
	return 1;
}

int check (double fpa[],double x,int i){
	if (x>=fpa[0] && x<= fpa[i-1])// checks if the value is in the range of the data that was read from the file 
	return 1;
	else {
	cout <<" the value is not in the ranage!! "<<endl;
	return 0;
     }
	
}

double interp (double fpa[], double col[], int i, double pth){
	double co,slope;
	int x=0;
	co=0;
	for (x=0;co==0;x++){// if the value is in the data give the answer that is in the table 
		if (pth == fpa[x]){
			co=col[x];
		}else{
			if (pth > fpa[x] && pth < fpa[x+1]){//if the value is in btw 2 point of the table use interpolation method to give an answer to the user 
				slope = (fpa[x+1]-fpa[x])/(col[x+1]-col[x]);
				co= (pth-fpa[x])/slope + col[x];
			}
		}
	}
	return co;
}
