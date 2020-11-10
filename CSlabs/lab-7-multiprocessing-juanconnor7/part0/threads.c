// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>
// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 64

int colors[NTHREADS][NTHREADS * 3];

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// Modify your paint function here
void *paint(void *vargp) {
	//pthread_mutex_lock(&mutex1);
	int peaks = 0;
	int colorCount = 3 * (int) vargp;

	for (int i = 0; i < NTHREADS * 3; i++) {
		int factor = (NTHREADS * 3) / 2;
		int increase = (255 / (64 / 6));
		int rgb = i / 3;
		if (peaks == 0) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = 0;
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 1;
					colorCount = 0;
				}
			}
			else { //BLUE
				colors[(int)vargp][i] = 255;
			}
		}
		else if (peaks == 1) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = 0;
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = 255;
			}
			else { //BLUE
				colors[(int)vargp][i] = 255 - colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 2;
					colorCount = 0;
				}
			}
		}
		else if (peaks == 2) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 3;
					colorCount = 0;
				}
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = 255;
			}
			else { //BLUE
				colors[(int)vargp][i] = 0;
			}
		}
		else if (peaks == 3) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = 255;
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = 255 - colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 4;
					colorCount = 0;
				}
				
			}
			else { //BLUE
				colors[(int)vargp][i] = 0;
			}
		}
		else if (peaks == 4) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = 255;
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = 0;

			}
			else { //BLUE
				colors[(int)vargp][i] = colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 5;
					colorCount = 0;
				}
			}
		}
		else if (peaks == 5) {
			if (i % 3 == 0) { //RED
				colors[(int)vargp][i] = 255 - colorCount;
				colorCount = colorCount + increase;
				if (colorCount >= 255) {
					peaks = 0;
					colorCount = 0;
				}
			}
			else if (i % 3 == 1) { //GREEN
				colors[(int)vargp][i] = 0;

			}
			else { //BLUE
				colors[(int)vargp][i] = 255;
			}
		}
	}
	
	//pthread_mutex_unlock(&mutex1);
	return NULL;
}

void save() {
	// Write out the PPM file
	FILE *fp;
	fp = fopen("pthread.ppm", "w+");
	fputs("P3\n", fp);
	fputs("64 64\n", fp);
	fputs("255\n", fp);
	for (int i = 0; i < NTHREADS; i++) {
		for (int j = 0; j < NTHREADS * 3; j++) {
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

	pthread_t tids[NTHREADS];

	// main loop 
	for (int i = 0; i < numberOfArtists; i++) {
		pthread_create(&tids[i], NULL, paint, i);
	}

	for (int i = 0; i < numberOfArtists; i++) {
		pthread_join(tids[i], NULL);
	}

	save();
	return 0;
}