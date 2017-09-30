//take me to las vegas made by Juan Pablo Bernal
// this program will simulate a game of dices  
//libraries
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
//sub function prototype
void getnumber(int& d1, int& d2, int&sum);


int main (void){

int dice1,dice2,count,balance,point,done,wager,x;
char rep;

ofstream outfile;
outfile.open("gamebal.txt");

do{// loop to play again if the user wants to 
x=0;
rep='n';//variable that will change if the user wants to play again 
balance= 1000;
srand(time(0));
// prompt the user 
cout << " Enter the wager you want for each game (remember that you start with 1000$) "<<endl;
outfile<< " Enter the wager you want (remember that you start with 1000$) "<<endl;
cin >> wager;
outfile<< " your wager for each game is  "<<wager<<" $"<<endl;
cout << " your wager for each game is  "<<wager<<" $"<<endl;

while (balance>=wager){//loop to keep playing until the balance is less than the wager 
	
	done = 0;
	
	while (done==0){//loop to keep rolling the dices until the player wins or loses 
		x++;
	outfile << "game # "<<x<<endl;
	cout << "game # "<<x<<endl;
	getnumber(dice1, dice2 , count);
	outfile << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl; 
    cout << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl;
    
	if (count == 7 || count == 11){//if sum is 7 or 11 player wins 
    	outfile << "player wins!"<<endl;
	    cout << "player wins!"<<endl;
	    done=1;
	    balance += wager;
        outfile << "your balance is :"<<balance<< "$"<<endl;	
        cout << "your balance is :"<<balance<< "$"<<endl;
	}else{
	
		if (count == 2 || count ==3 || count ==12 ){//if sum is 2 3 or 12 player loses 
			outfile << "game over!! :( "<<endl;
	        cout << "game over!! :( "<<endl;
	        done=1;
	        balance -= wager;
            outfile << "your balance is :"<<balance<< "$"<<endl;	
            cout << "your balance is :"<<balance<< "$"<<endl;
		}else{
			point =count;
	
			while (done==0){//loop to roll the dice until the sum is the same as the point or 7
				getnumber(dice1, dice2 , count);
				outfile << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl; 
                cout << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl;
    
	                if (count==point){
                    	outfile << "player wins!"<<endl;
	                    cout << "player wins!"<<endl;
	                    done=1;	
	                     balance += wager;
                         outfile << "your balance is :"<<balance<< "$"<<endl;	
                         cout << "your balance is :"<<balance<< "$"<<endl;
					}else {
	
						if (count==7){
						outfile << "game over!! :( "<<endl;
	                    cout << "game over!! :( "<<endl;
	                    done=1;
	                     balance -= wager;
                         outfile << "your balance is :"<<balance<< "$"<<endl;	
                         cout << "your balance is :"<<balance<< "$"<<endl;				
						}				
					}
			}
		}
	}
}
}
//loop to roll the dice until the sum is the same as the point or 7
outfile << "You´r busted! your balance is : "<<balance<<"$ and you played "<<x<<" times.  Do you want to play again? press y to play again press n to finish"<<endl;
cout << "You´r busted! your balance is : "<<balance<<"$ and you played "<<x<<" times.  Do you want to play again? press y to play again press n to finish"<<endl;
cin >> rep;

}while(rep=='y');

outfile  << "thx for playing :)";
cout << "thx for playing :)";

return 0;	
}

void getnumber(int& d1, int&d2, int& sum){//function to generate random numbers from 1 to 6 and sum them 

	d1=(rand()%6+1);
	d2 = (rand()%6+1);
	sum= d1+d2;

}
