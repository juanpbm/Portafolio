// made by Juan Pablo Bernal
// this program will process some data and find some specific values like max or max average   
//libraries
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std; 
//sub function prototype
void deepest(double depth[][6], int& f,int& c);
void deepest_area(double depth[][6], int& f,int& c,double& maxav);

int main (void){
	
	double data[6][6],maxav=0; 
	int i,x,f,c;
	ifstream infile;//open the file read it and store it in a 2-d array
	infile.open("depth.txt");
	cout <<"The depth matrix is: (Note that the coordinates are given in (row,column)) "<<endl;
	for (i=0; i<6 ;i++){
		for (int x=0;x<6; x++){
		 infile >> data[i][x];
		 cout << data[i][x]<<"   ";
		}
	cout<< endl;
	}
    deepest( data, f, c);//call the sub function to find the deepest point and show the value to the user 
    cout <<"The deepest point in the ocean is "<<data[f][c]<<"m occurring at coordinates ("<<f+1<<","<<c+1<<")"<<endl; 
	deepest_area(data, f, c,maxav);//call the sub function to find the deepest 2x2 area and show the value to the user 
	cout << "The deepest 2 X 2 area in the ocean is "<<maxav<< "m Bounded by ("<<f+1<<","<<c+1<<") and ("<<f+2<<","<<c+2<<")"<<endl;
	
	return 0;
}

void deepest(double depth[][6], int& f,int& c){//find the deepest point
	
	int i,x;
	double max=depth[0][0];//give max a value and compare it with all the others when it finds a larger value the max value changes and it is the new value to be compared.
		for (i=0; i<6 ;i++){
		    for (x=0;x<6; x++){
	         if	(depth [i][x]>max){
		  	 max= depth[i][x];
		  	 f=i;
		  	 c=x;
	}
	}
}
}
void deepest_area(double depth[][6], int& f,int& c,double& maxav){
	
	int i,x;
	double av;//do the same as the previous sub function but now the average of the depth of the 2x2 area is what is going to be compared. 
		for (i=0; i<5 ;i++){
	    	for (x=0;x<5; x++){
	         av= (depth[i][x]+depth[i+1][x]+depth[i][x+1]+depth[i+1][x+1])/4;
	         if	(av>maxav){
		  	maxav=av;
		  	f=i;
		  	c=x;
	}
	}
}
}
