// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h>
// Create your node_t type here


// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.


typedef struct node{ // Note typedef saves us some typing so we do not have to type 'struct' everytime.
    int myData;
    struct node* next;
} node_t;

node_t* redSoxDataLL;

void create_list() {

	// pointer to file
	FILE* redSoxData;

	// initialize file pointer
	redSoxData = fopen("./data.txt","r");

	// check
	if(NULL == redSoxData){
       		fprintf(stderr,"data.txt not found, did you run data.sh?");
        	fprintf(stderr,"note: stderr argument means we write to a special 'error' output stream.");
        	fprintf(stderr,"Program terminating now...");
        	exit(1);
	}

	// Read the file and fill Linked list 
	node_t* currNode = (node_t*)malloc(sizeof(node_t));
	char buffer[255];
	int listSize = 0;
	

	while(fscanf(redSoxData, "%s", buffer) != EOF){

		currNode -> myData = atoi(buffer);
		node_t* nextNode = (node_t*)malloc(sizeof(node_t));
		currNode -> next = nextNode;
		if (listSize == 0)
			redSoxDataLL = currNode;
		currNode = nextNode;
		currNode -> next = NULL;
		listSize += 1;	      	
    	}
	//close the txt file 	
	fclose(redSoxData);
}

//function to print the linked list 
void print_list (){
	node_t* node = redSoxDataLL;
	while (node -> next != NULL){
		printf("%d \n", node -> myData);
		node = node -> next;
	}
}

// function to free the space 
void free_list(){
	node_t* node = redSoxDataLL;
	node_t* tempNode;
	while (node -> next != NULL){
		tempNode = node -> next;
		free(node);
		node = tempNode;
	}
	free(node);
	printf("The memory is free");
}

int main(){
	create_list(); 
	print_list();
	free_list();
	return 0;
}
