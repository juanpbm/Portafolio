// Write a C program that swaps two integers in a function


#include <stdio.h>

void swap(int x, int y){

	int temp;

	temp = x;
	x = y;
	y = temp;
}


int main(){
	
	int x = 6;
	int y = 10;

	swap(x, y);
}
