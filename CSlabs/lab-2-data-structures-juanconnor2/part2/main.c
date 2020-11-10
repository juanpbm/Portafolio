// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "mystack.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1(){

	stack_t* test1 = create_stack(MAX_DEPTH);
	printf("Attempting to push %d\n",1);
	stack_enqueue(test1,1);	
	printf("Removing: %d\n",stack_dequeue(test1));	

	free_stack(test1);
}

void unitTest2(){
	stack_t* test1 = create_stack(3);
	printf("Checking if empty\n");
	if(stack_empty(test1) == 1) {
		printf("correctly found to be empty\n");
	} else {
		printf("incorrectly found to be not empty\n"); 
	}
	stack_enqueue(test1, 1);
	printf("Checking if full\n");
	if(stack_full(test1) == 0) {
		printf("correctly found to be not full\n");
	} else {
		printf("incorrectly found to be full\n");
	}
	stack_enqueue(test1, 2);
	stack_enqueue(test1, 3);
	printf("Checking if full\n");
	if(stack_full(test1) == 1) {
		printf("correctly found to be full\n");
	} else {
		printf("incorrectly found to be not full\n");
	}
}


void unitTest3(){
	stack_t* test1 = create_stack(1);
	printf("Attempting enqueue\n");
	if(stack_enqueue(test1, 1) == 0) {
		printf("successfull\n");
	} else {
		printf("unsuccesfull\n");
	}
	printf("Attempting enqueue on full\n");
	if(stack_enqueue(test1, 2) == -1) {
		printf("successfully failed\n");
	} else {
		printf("unsuccessfully succeeded\n");
	}
	printf("Attempting dequeue\n");
	if(stack_dequeue(test1) == 1) {
		printf("successful\n");
	} else {
		printf("unsuccessful\n");
	}
	printf("Attempting to dequeue on empty (succeeds if no success statement follows)\n");
	stack_dequeue(test1);
	printf("unsuccessfully succeeded\n");

		
	
}
void unitTest4(){
	stack_t* test1 = create_stack(2);
	printf("Attempting stack_size on empty stack\n");
	if(stack_size(test1)==0) {
		printf("succeeded\n");
	} else {
		printf("failed\n");
	}
	stack_enqueue(test1, 1);
	printf("Attempting stack_size on stack of 1\n");
	if(stack_size(test1) == 1) {
		printf("succeeded\n");
	} else {
		printf("failed\n");
	}
	printf("Attempting stack_size on null (succeeds if no success statement follows)\n");
	stack_size(NULL);
	printf("failed\n");
	
	
}
void unitTest5(){
	stack_t* test1 = create_stack(5);
	stack_enqueue(test1, 5);
	stack_enqueue(test1, 30);
	printf("attempting free_stack (fails if no success statement follows)\n");
	free_stack(test1);
	printf("succeeded");
}


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
	unitTest1();
	unitTest2();
	unitTest3();
	unitTest4();
	unitTest5();
	return 0;
}
