// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "myqueue.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1(){
	
	printf("----test1----\n");
	queue_t* test1 = create_queue(1);
	printf("Attempting to add %d\n",1);
	queue_enqueue(test1,1);	
	printf("Removing: %d\n",queue_dequeue(test1));	

	free_queue(test1);
}

void unitTest2(){
	
	printf("----test2----\n");
	queue_t* test2 = create_queue(4);
	for(int i = 0; i < 4; i++){
		queue_enqueue(test2, i+2);
		printf ("%d is in the queue\n",i+2);	
	}

	for(int i = 0; i < 4; i++){
		printf ("%d has been removed\n", queue_dequeue(test2));
	}

	for(int i = 0; i < 4; i++){
		queue_enqueue(test2, i+4);
		printf ("%d is in the queue\n",i+4);	
	}

	free_queue(test2);
}

void unitTest3(){
	
	printf("----test3----\n");
	queue_t* test3 = create_queue(4);
	for(int i = 0; i < 5; i++){
		if(!queue_enqueue(test3, i)){;
			printf ("%d is in the queue\n",i);	
		}else{
			printf("%d could not be added, the queue is full\n", i);
		}
	}
	
	free_queue(test3);
}

void unitTest4(){

	printf("----test4---\n");
	queue_t* test4 = create_queue(4);
	while(!queue_full(test4)){
		queue_enqueue(test4, 5);
		printf ("%d is in the queue\n", 5);
	}

	printf("the queue has %d elements\n",queue_size(test4));

	while(!queue_empty(test4)){

		queue_dequeue(test4);
	}
	
	free_queue(test4);
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
	return 0;
}
