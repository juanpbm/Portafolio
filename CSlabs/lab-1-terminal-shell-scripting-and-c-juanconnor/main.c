// Insert your code here
#include <stdio.h>
#include <math.h>

double power (double base, double n){
	double sol = 2;
	for (int i = 0; i < n; i++){
		sol = sol * 2;
	}
	
	return sol; 
}
int main (){
	double x;
	for (double i = 0; i < 10; i++){
		x = power( 2, i);
		printf("%.0lf \n", x);	
	}
}
