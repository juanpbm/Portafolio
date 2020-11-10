// Write a C program using a switch statement

#include <stdlib.h>
#include <stdio.h>


int main(){

	char dir = 'U';
	int x = 3;
	switch(dir){

		case 'L':
			x -= 1;
			break;

		case 'R':
			x += 1;
			break;		
		
		case 'U':
			x += 2;
			break;

		case 'D':
			x -= 2;
			break;
	}
	return 0;
}
