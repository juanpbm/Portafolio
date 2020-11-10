#include <stdio.h>
#include <unistd.h>

void msg(){
	sleep(1);
	printf("Hello!\n");
}


int main(){

	int i;
	for(i= 0;i  < 10; ++i){
		msg();
	}

	return 0;
}
