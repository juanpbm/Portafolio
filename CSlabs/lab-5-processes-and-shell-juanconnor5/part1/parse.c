// Implement a lexer parser in this file that splits text into individual tokens.
// You may reuse any functions you write for your main shell.
// The point is that you get something small working first!
#include<string.h>
#include<stdio.h>
#include<stdlib.h>



int main(int argc, char **argv){

	if (argc > 1){
		char* commands = strtok(argv[1], " ");

		while (commands != NULL){

			printf("%s\n",commands);
			commands = strtok(NULL, " ");

		}	
	}else{
		printf("no arguments");
	}
return 0;
}
