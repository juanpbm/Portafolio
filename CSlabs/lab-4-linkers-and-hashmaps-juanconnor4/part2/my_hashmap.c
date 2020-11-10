// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf  output. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// - You may add any helper functions that you think you need (if any, or otherwise for debugging)
// ==================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "containers.h"
#include "my_hashmap.h"


// Simple hash function that will put a key into a bucket
// The module operator will make sure we do not go out of bounds.
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
hashmap_t* hashmap_create(unsigned int _buckets){
    // Allocate memory for our hashmap
	hashmap_t* myMap = (hashmap_t*)malloc(sizeof(hashmap_t));// + _buckets*sizeof(node_t));
    // Set the number of buckets
	myMap -> buckets = _buckets;
    // Initialize our array of lists for each bucket
    	myMap -> arrayOfLists = (node_t**)malloc(sizeof(node_t*) * _buckets);
	for (int i = 0; i < _buckets; i++){
		node_t* node = (node_t*)malloc(sizeof(node_t));
		pair_t* pair = (pair_t*)malloc(sizeof(pair_t)); 
		pair -> value = NULL;
		pair -> key = NULL;
		node -> kv = pair;
		node -> next = NULL;
		myMap -> arrayOfLists[i] = node;
	} 
    // Setup our hash function to point to our
    // stringHash function.
	myMap -> hashFunction = &stringHash;
    // Return the new map that we have created
    return myMap;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// Attempting to delete a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap){
	if(_hashmap != NULL){
		for (int i = 0; i < _hashmap -> buckets; i++){
			node_t* curr = _hashmap -> arrayOfLists[i];
			while (curr -> next != NULL){
			
				node_t* nxt = curr -> next;
				free(curr);
				curr = nxt;
			}
			free (curr);
		}
	
		free(_hashmap);
	}else{
		exit(1);
	}	
}

// Returns a boolean value if a key has been put into
// the hashmapi
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Attempting hashmap_hasKey on a NULL hashmap should exit(1)
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search (i.e. iterate through) that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key){

	int i = _hashmap -> hashFunction (key, _hashmap -> buckets);
	node_t* curr = _hashmap -> arrayOfLists[i];

	do {
		if (curr -> kv -> key != NULL){
			if (strcmp(curr -> kv -> key,key) == 0){
				return 1;
			}
		}
		
		curr = curr -> next; 
	}while(curr != NULL); 
	
	return 0;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
//  - Attempting hashmap_insert on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value){

	if (!hashmap_hasKey(_hashmap, key)){
		
		int i = _hashmap -> hashFunction(key, _hashmap -> buckets);
		node_t* curr = _hashmap -> arrayOfLists[i];
			
		if (curr -> kv -> key == NULL){
		
			curr -> kv -> key = key;
			curr -> kv -> value = value;
			curr -> next  = NULL;
		}else{

			while (curr -> next != NULL){

				curr = curr -> next; 
			}	

			node_t* newnode = (node_t*)malloc(sizeof(node_t));
			pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
			newnode -> kv = newpair;
			newnode -> kv -> key = key;
			newnode -> kv -> value = value;
			newnode -> next = NULL;
			curr -> next = newnode; 
		}
		
		return;
	}
}

// Return a value from a key 
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
//  - Attempting hashmap_getValue on a NULL hashmap should exit(1)
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key){
	if (hashmap_hasKey(_hashmap, key)){

		int i = _hashmap -> hashFunction(key, _hashmap -> buckets);
		node_t* curr = _hashmap -> arrayOfLists[i];

		do {
			if (curr -> kv -> key != NULL){
				if (strcmp(curr -> kv -> key,key) == 0){
					return curr -> kv -> value;
				}
			}
			
			curr = curr -> next; 
		}while(curr != NULL); 		
	}
	return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
//  - Attempting hashmap_removeKey on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key){
	if (hashmap_hasKey(_hashmap, key)){

		int i = _hashmap -> hashFunction(key, _hashmap -> buckets);
		node_t* curr = _hashmap -> arrayOfLists[i];
		node_t* last = _hashmap -> arrayOfLists[i];

		do {
			if (curr != last){
				if (curr -> kv -> key != NULL){
					if (strcmp(curr -> kv -> key,key) == 0){
						last -> next = curr -> next;
						free (curr);
						return;
					}
				}
			}else{
				if (curr -> kv -> key != NULL){
					if (strcmp(curr -> kv -> key,key) == 0){
						if (curr -> next == NULL){
							curr -> kv -> key = NULL;
							curr -> kv -> value = NULL;				
							return;
						}else{
							_hashmap -> arrayOfLists[i] = curr -> next;
							free(curr);	
							return;
						}
					}	
				}
			}
			last = curr;
			curr = curr -> next; 
		}while(curr != NULL); 
			
	}
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
//  - Attempting hashmap_update on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue){
	if (hashmap_hasKey(_hashmap, key)){

		int i = _hashmap -> hashFunction(key, _hashmap -> buckets);
		node_t* curr = _hashmap -> arrayOfLists[i];

		do {
			if (curr -> kv -> key != NULL){
				if (strcmp(curr -> kv -> key,key) == 0){
					curr -> kv -> value = newValue;
				}
			}
			
			curr = curr -> next; 
		}while(curr != NULL); 			
	}
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
//  - Attempting hashmap_printKeys on a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	for (int i = 0; i < _hashmap -> buckets; i ++){
		node_t* curr = _hashmap -> arrayOfLists[i];

		do {
			if (curr -> kv -> key != NULL){
				printf("%s\n", curr -> kv -> key); 
			}
			
			curr = curr -> next; 
		}while(curr != NULL); 
	}	
			
}
