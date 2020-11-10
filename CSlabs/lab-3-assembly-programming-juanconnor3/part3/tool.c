#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


void addToCommands(int array[], char str[], int numCommands, char commandsKnown[][1000]) {
	for(int i = 0; i < numCommands; i++) {
		if(strstr(str, commandsKnown[i]) != NULL) {
			array[i] = array[i] + 1;
		}
	}
	

}

int cycleAmount(int cyclesOfCommand[], int numCommands, int array[]) {
	int cycles = 0;
	for(int i = 0; i < numCommands; i++) {
		cycles = cycles + (cyclesOfCommand[i] * array[i]);
	}
	return cycles;
}



int main(int argc, char *argv[]) {
	char c[1000];
	FILE *file;
	char ch;
	char commandsKnownArray[][1000] =
	{"add", "sub", "mul", "div",
	 "mov", "lea", "push", "pop",
	 "ret"
	};
	int cyclesOfCommand[] =
	{1    , 1    , 1   , 4    ,
         1    , 1    , 1    , 1    ,
         1
	}; 
	int commandsKnown = (sizeof(commandsKnownArray)/sizeof(commandsKnownArray[0]));
	int commands = 0;
	int commandArray[commandsKnown];

	for(int i = 0; i < commandsKnown; i++) {
		commandArray[i] = 0;
	}
	
	if(argc != 2) {
		printf("Incorrect number of arguments");
		exit(1);
	}
	
	file = fopen(argv[1], "r");
	if(file == NULL) {
		printf("Invalid file");
	}
	
	while (fgets(c, 1000, file) != NULL) {
		addToCommands(commandArray, c, commandsKnown, commandsKnownArray);
		//printf("%s", c);
	} 
	fclose(file);

	commands = 0;
	for(int i = 0; i < commandsKnown; i++) {
		printf("%s: %d\n", commandsKnownArray[i], commandArray[i]);
		commands = commands + commandArray[i];
	}
	printf("Total Instructions = %d\n", commands);
	printf("Total Cycles = %d\n", cycleAmount(cyclesOfCommand, commandsKnown, commandArray));	
	return 0;
}











