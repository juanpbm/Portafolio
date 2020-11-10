#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

#define BUFFER_SIZE 80

int exitVal = 1;// make 0 to exit the while
pid_t pid;
char* shellColor = "\033[0m";
void exitInShell(char* command[BUFFER_SIZE]) {
	printf("mini-shell terminated\n");
	exitVal--;
}

void helpInShell(char* command[BUFFER_SIZE]) {
	printf("Shell Commands:\n - cd [directory]\n     Changes directory.\n - exit\n     Exits the shell.\n - help\n     Prints this help message.\n - shellColor.\n     Changes the color of the mini-shell prompt\n     Colors supported are green, yellow, red, clear\n");
}


//Signal handler

void sigint_handler(int sig) {

	write(1, "Terminating through signal handler\n", 35);
	exitInShell(NULL);
	exit(0);

}

// cd
void cd(char* command[BUFFER_SIZE]) {
	if(argsInCommand(command) == 1) {
		chdir("~");
		return;
	} else if(argsInCommand(command) == 2) {
			chdir(command[1]);
			return;
		}
		printf("Invalid args for cd\n");
		return;

	if(sizeof(command) < sizeof(char)*2) {
		return;
	}
}

int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre));
}

void executeExecutable(char* command[BUFFER_SIZE]) {
	pid_t pid = fork();
	if(pid==0) {
		execve(command[0], command, NULL);
		int failed = -22;
		failed = execve(command[0], command, NULL);
		if(failed != -22) {
				printf("mini-shell> Command not found--Did you mean something else?\n");
		}
		exit(1);
	}
	wait(NULL);
}

int argsInCommand(char* command[BUFFER_SIZE]) {
	int length = -1;
	while(command[++length] != NULL) {}
	return length;
}

void executeStandardCall(char* command[BUFFER_SIZE]) {

	char binCommand[BUFFER_SIZE];
	memset(binCommand, 0, BUFFER_SIZE);
	strcat(binCommand, "/bin/");
	strcat(binCommand, command[0]);
	command[0] = binCommand;
	executeExecutable(command);
}



void pipeInShell(char* command[], int pipeLocation, int end) {
	const char *inCommand[BUFFER_SIZE];
	const char *receiveCommand[BUFFER_SIZE];
	for(int i = 0; i < end; i++) {
		if(i < pipeLocation) {
			inCommand[i] = command[i];
		} else if (i == pipeLocation) {
			inCommand[i] = NULL;
		} else {
			receiveCommand[(i - pipeLocation - 1)] = command[i];

		}
		receiveCommand[end - pipeLocation - 1] = NULL;
	}


	  int fds[2];
	  pipe(fds);

    pid_t pid = fork();
		//read in child
	  if (pid == 0) {

	    dup2(fds[0], STDIN_FILENO);
	    close(fds[0]);
	    close(fds[1]);
			executeStandardCall(receiveCommand);
			exit(0);
	  }

	  close(fds[0]);
		int saveSTDOUT = dup2(1);
		dup2(fds[1], 1);
		pid_t pid1 = fork();
 
	  if (pid1 == 0) {
			const char *commands2[] = {"cat", "shell.c", NULL};
			executeStandardCall(inCommand);
			exit(0);

		}
		dup2(saveSTDOUT, 1);

	  close(fds[1]);

	  int status;
	  pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting


}
void changeShellColor(char* command[BUFFER_SIZE]) {
	if(argsInCommand(command) != 2) {
		printf("Only accepts 1 argument for color\n");
		return;
	}
	char colorCodes[4][BUFFER_SIZE] = {
		"\033[0;32m",
		"\033[1;33m",
		"\033[0;31m",
		"\033[0m"
	};
	char colorNames[4][BUFFER_SIZE] = {
		"green",
		"yellow",
		"red",
		"clear"
	};
	for (int i = 0; i < 4; i++){
			if (strcmp(colorNames[i], command[1]) == 0){
				shellColor = colorCodes[i];
				return;
			}
		}
	printf("unknown color\n");
	//shellColor = GREEN;
}

void printShellLabel() {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf ("\033[1;32m");
	printf ("mini-shell ");
	printf("\033[0;36m");
	printf("[%s]> ", cwd);
	printf(shellColor);
}

int main() {

  char* temp;// temp variable to parse the input string
  char* command[BUFFER_SIZE];// it will contain the comands in an array
  int counter;// how many argumets are in the input
  char str[BUFFER_SIZE];// string from user
  char listOfCommands[4][BUFFER_SIZE] = {"cd","help","exit","shellColor"};//add here the supported comands
	void (*functions[4]) (char* inputCommand[BUFFER_SIZE]);
	int pipeflag[] = {0,0};
	functions[0] = &cd;
	functions[1] = &helpInShell;
	functions[2] = &exitInShell;
	functions[3] = &changeShellColor;

	char* commandTest[BUFFER_SIZE];
	commandTest[0] = "/bin/cat2";
	commandTest[1] = "shell.c";
	commandTest[2] = NULL;
	signal(SIGINT, sigint_handler);

	while (exitVal == 1) {
		printShellLabel();

		//reset strings and counter
		memset(command,0,sizeof(command));
		memset(str,0,sizeof(str));
		counter = 0;

		fgets (str, BUFFER_SIZE, stdin);
		// parse the string
		temp = strtok(str, " ");
		while (temp != NULL){
			if (strcmp(temp, "|") == 0){
	      			pipeflag[0] = 1;
	      			pipeflag[1] = counter;
      			}
      			command[counter] = temp;
     	 		temp = strtok(NULL, " ");
      			counter ++;
    		}



		if (strcmp(command[0],"\n") != 0){
			//remove the newline and append null
			temp = strtok(command[counter - 1], "\n");
			command[counter - 1] = temp;
			command[counter] = NULL;

			int knownCommandFound = 0;
	   	 	for (int i = 0; i < 4; i++){
	   	 		if (pipeflag[0] == 0){
        				if (strcmp(listOfCommands[i], command[0]) == 0){
            					knownCommandFound = 1;
						(*functions[i]) (command);
		       			}
	    			}else{
		    			i = 3;
		    			pipeInShell(command, pipeflag[1], counter);
	    			}
      			}

			if (knownCommandFound != 1 && pipeflag[0] == 0) {
				//is not a base command in /bin
				if(prefix("/", command[0]) == 0 || prefix(".", command[0]) == 0) {
					executeExecutable(command);

				} else {
					//is a command in /bin
					executeStandardCall(command);
				}
			}
		pipeflag[0] = 0;
		execve(commandTest[0], commandTest, NULL);
		}
	}
return 0;
}
