// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char colors[64][64 * 3];
int curRow = 0;
// Modify your paint function here
void paint(int workID) {
	printf("Artist %d is painting\n", workID);
	for (int i = 0; i < 64 * 3; i++) {
		if (i % 3 == 0) { //RED
			colors[curRow][i] = 0;
		}
		else if (i % 3 == 1) { //GREEN
			colors[curRow][i] = (255 + (i * 2) - curRow) % 255;
		} 
		else { //BLUE
			colors[curRow][i] = (255 - (i * 2) - curRow) % 255;
		}
	}
	curRow = curRow + 1;
}

void save() {
	// Write out the PPM file
	// If you are looking at this solution, it could
	// be better laid out in a 'save function'
	FILE *fp;
	fp = fopen("vfork.ppm", "w+");
	fputs("P3\n", fp);
	fputs("64 64\n", fp);
	fputs("255\n", fp);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64 * 3; j++) {
			fprintf(fp, "%d", colors[i][j]);
			fputs(" ", fp);
		}
		fputs("\n", fp);
	}
	fclose(fp);
}
int main(int argc, char** argv) {

	int numberOfArtists = 64; // How many child processes we want
	int* integers = malloc(sizeof(int) * 8000);
	
	pid_t pid;
	// main loop where we fork new threads
	for (int i = 0; i < numberOfArtists; i++) {
		// (1) Perform a fork
		pid = vfork();


			// (2) Make only the child do some work (i.e. paint) and then terminate.
			if (pid == 0) {
				// TODO: make child paint
				paint(getpid());
				exit(0);
				// TODO: Then terminate/exit child
			}
	}

	pid_t wpid;
	int status = 0;
	while ((wpid = wait(&status)) > 0);

	printf("parent is exiting(last artist out!)\n");

	free(integers);
	save();
	return 0;
}