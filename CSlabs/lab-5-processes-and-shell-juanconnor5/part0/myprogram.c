#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int main(){

	char* co1[3];	// We can store up to 16 arguments.
	co1[0]="/bin/ls";	// Our first argument is the program we want to launch.
	co1[1]="-F";	
	co1[2]=NULL;
	char* co2[3];
	co2[0] = "/bin/nl";
	co2[1] = "example2.c";
	co2[2] = NULL; 
	char* co3[5];
	co3[0] = "/bin/pwd";
	co3[1] = NULL;

	
	if (fork() == 0){
		if (fork() == 0){
			execve(co1[0],co1,NULL);
			printf("Child: Should never get here\n");
			exit(1);
	}
		execve(co2[0],co2,NULL);
		printf("Child: Should never get here\n");
		exit(1);
	}else{
		execve(co3[0],co3,NULL);
		printf("Child: Should never get here\n");
		exit(1);
	}

return 0;
}
