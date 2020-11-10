// Write a C program that calls an add function(long add(long a, long b).

#include <stdlib.h>
#include <stdio.h>

long add(long a, long b){
	
	return a + b;
}

int main(){

	long a = 5;
	long b = 10;

	printf("%ld + %ld = %ld\n", a, b, add(a, b));

	return 0;
}
