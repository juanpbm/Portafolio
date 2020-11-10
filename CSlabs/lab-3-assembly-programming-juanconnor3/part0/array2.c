// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
//
#include <stdio.h>
#include<stdlib.h>

int main(){

	int* a = (int*)malloc(400*sizeof(int));

	a[0] = 351;
	a[50] =32;
	a[95] = 43;
	a[123] = 450;
	a[200] = 3254;
	a[250] = 2;
	a[399] = 77;
	return 0;
}
