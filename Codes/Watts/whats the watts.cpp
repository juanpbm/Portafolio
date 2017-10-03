// made by Juan Pablo Bernal
// this program  will process de data from a file and let the user get the averages that he needs
//libraries
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;
#define nrows 10
#define ncols 7

//sub function prototype
void min(double power[][ncols]);
double week_average(double test_array[][ncols],int test_row );

int main (void){
	double watt[nrows][ncols],count,av;
	int i,x,test=0,d=0,test1;
	char cho;
	ifstream infile;
	infile.open("power.txt");//open the file read it and store it in a 2-d array
	for (i=0; i<nrows ;i++){
		for (int x=0;x<ncols; x++){
		 infile >> watt[i][x];
		 cout << watt[i][x]<<"   ";
		}
    	cout<< endl;
	}
	for (i=0; i<nrows ;i++){//loop top get the average for all the values 
		for (int x=0;x<ncols; x++){
		 count += watt[i][x];
		}
	}
	cout << "The average power output over these 10 weeks is: "<<count/70<<endl;
	min(watt);//minimum sub function
	while (d==0){//loop to ask the user which average does he wants 
	cout <<"If you want the average for a specific week enter 'E', for the average of a range of weeks enter 'R', or for the average of every week enter 'W' "<<endl;
	cin >> cho;	
	if (cho == 'e' || cho == 'E'){//if he want only one week prompt the user to get the value of the week that he wants to evaluate  
	  while (test<=0 || test>=nrows+1){//loop to check if the value entered is in the range 
   	     cout <<"Please enter the row that you want to evaluate (1-10)";
	     cin >>test;
	     }
	     test-=1; cout << "The average for week #"<<test+1<< " is: "<< week_average(watt,test)<<endl;//call the function to get the average 
         d=1;
	    }else if (cho=='R' || cho =='r'){//if the user wants a range of weeks get the values of that range and check if they are in the range of data
	    	while ((test<=0 || test>=nrows+1) || (test1<=0 || test1>=nrows+1)){
	         cout <<"please enter the range of weeks that you want to evaluate (1-10)";
 	         cin >>test >> test1;
 	         }
 	         test-=1;
 	         test1-=1;
   	         for (int k=test;k<=test1;k++){//call the function for every value of the range that the user entered
             cout << "Week #"<<k+1<< ": Average power output in Megawatts is: "<< week_average(watt,k)<<endl;
		     av+=week_average(watt,k);
	         }
             cout <<"The total average from week #"<<test+1<< " to week #"<<test1+1<< " is: "<<av/(test1-test+1)<<" Watts";
	         d=1;
	        }else if (cho=='W'|| cho =='w'){//if the user wants all the values a loop that will go through all the weeks that the data has
        	     for (test=0;test<nrows;test++){
                 cout << "Week #"<<test+1<< ": Average power output in Megawatts is: "<< week_average(watt,test)<<endl;
                 }
                 d=1;
                }else//if the user entered a wrong letter the program will ask for it again until the user enters the correct letter.
                     cout << "ERROR!!! \nonly enter E for an specific week, R for a range or W for all of them";
    }
	return 0;

}


void min(double power[][ncols]){//sub function to find the minimum value and show it to the user every time that appears in the data file 	
	int i,x;
	double min=power[0][0];
	for (i=0; i<nrows ;i++){//find min
		for (int x=0;x<ncols; x++){
	    if 	(power[i][x]<min){
		  	min= power[i][x];
	    }   
    	}
    }
   	for (i=0; i<nrows ;i++){//show min
		for (int x=0;x<ncols; x++){
	    if 	(power[i][x]==min){
		  cout << "the minimum output ("<< min<<" W) occurred in the week #"<<i+1<<" the day# "<<x+1<<endl; 
	    }
    	}
    }
}

double week_average(double test_array[][ncols],int test_row ){/*sub function that will get the average of an specific week given by the user in
 case of the range or all of them the value of the week is given by a for loop*/
	
	int x;	
	double count;
	for (int x=0;x<ncols; x++){
	count += test_array[test_row][x];
    }
	
	return count/7;
}
