// Basic test

#include <stdio.h>
#include <malloc.h>

#define DATA_SIZE 2048

int main(){

  // Allocate some data
  int* data1 = (int*)malloc(2048);
  //int* data2 = (int*)malloc(DATA_SIZE);
  
  // Do something with the data
  int i=0;
  for(i =0; i < DATA_SIZE; i++){
    data1[i] = i;
	//printf("trying to assign data at %zu\n", (void*) &data1[i]);
	//printf("data: %d\n", data1[i]);
  }
  printf("data: %d\n", data1[25]);
  /*
  int j = 0;
  for (j = 0; j < DATA_SIZE; j++) {
	  data2[j] = j; 
	  //printf("data: %d\n", data2[j]);
  }*/
  
  //printf("data: %d\n", data2[44]);
  // Free the data
  free(data1);
  //free(data2);
  printf("data: %d\n", data1[56]);
  int* data2 = (int*)malloc(2048);
  //printf("data: %d\n", data2[44]);
  
  return 0;
}
