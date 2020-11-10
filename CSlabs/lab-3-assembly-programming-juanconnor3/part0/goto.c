// Write a C program using the goto command and a label.


#include <stdlib.h>
#include <stdio.h>

int main(){

	int x = 5;
	
	x += 10;
	goto SKIP;
	x = 10;
	SKIP: x = 0;

	return 0;
}
