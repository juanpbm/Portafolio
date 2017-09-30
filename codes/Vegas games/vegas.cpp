//take me to las vegas made by Juan Pablo Bernal 
// this program will simulate a game of dices 
// libaries 
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
// subfunction prototype
void getnumber(int& d1, int& d2, int&sum);


int main (void){

int dice1,dice2,count,games,point,done;
char rep;
ofstream outfile;
outfile.open("game.txt");

do{// loop to play again if the user wants to

rep='n';//variable that will change if the user wants to play again 
srand(time(0));
// prompt the user
cout << "pleas enter the number of times you want to play from 5 to 20"<<endl;
outfile<< "pleas enter the number of times you want to play from 5 to 20"<<endl;
cin >> games;
outfile<< "\nyou want to play "<<games<<" times"<<endl;

for (int x=1; x<=games ;x++){
	
	done = 0;
	
	while (done==0){//loop to keep rolling the dices until the player wins or loses 
	outfile << "game # "<<x<<endl;
	cout << "game # "<<x<<endl;
	getnumber(dice1, dice2 , count);
	outfile << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl; 
    cout << "player roled "<< dice1<<" + " <<dice2<<"="<<count<<endl;
    
	if (count == 7 || count == 12){
    	outfile << "player wins!"<<endl;
	    cout << "player wins!"<<endl;
	    done=1;
	
	}else{
	
		if (count == 2 || count ==3 || count ==12 ){
			outfile << "game over!! :( "<<endl;
	        cout << "game over!! :( "<<endl;
	        done=1;
	
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
	
					}else {
	
						if (count==7){
						outfile << "game over!! :( "<<endl;
	                    cout << "game over!! :( "<<endl;
	                    done=1;
						}				
					}
			}
		}
	}
}
}
//loop to roll the dice until the sum is the same as the point or 7
outfile << "do you want to play again? pres y to play again press n to finish"<<endl;
cout << "do you want to play again? pres y to play again press n to finish"<<endl;
cin >> rep;

}while(rep=='y');

outfile  << "thx for playing :)";
cout << "thx for playing :)";

return 0;	
}

void getnumber(int& d1, int&d2, int& sum){//function to generate rendom numbers from 1 to 6

	d1=(rand()%6+1);
	d2 = (rand()%6+1);
	sum= d1+d2;

}
