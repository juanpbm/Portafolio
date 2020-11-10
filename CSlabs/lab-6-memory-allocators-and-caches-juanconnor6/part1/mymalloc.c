#include <stdio.h> // Any other headers we need here
#include <malloc.h> // We bring in the old malloc function
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct block{
	size_t size; // How many bytes beyond this block have been allocated in the heap
	struct block* next; // Where is the next block in your linked list
	int free; // Is this memory free?
	int debug; // (optional) Perhaps you can embed other information--remember, you are the boss!
}	block_t;

#define ALLOC_UNIT 3 * sysconf(_SC_PAGESIZE)
#define BLOCK_SIZE = sizeof(block_t)

static block_t *freeHead = NULL;
static block_t *allocatedHead = NULL;
int counter = 0;

void removeFromAllocated(void *ptr) {
	struct block *tempBlock = allocatedHead;
	struct block *prev = tempBlock;
	if (ptr == tempBlock) {
		allocatedHead = tempBlock->next;
		return;
	}
	else {
		tempBlock = tempBlock->next;
		while (tempBlock) {
			if (ptr == tempBlock) {
				prev->next = tempBlock->next;
				return;
			}
			tempBlock = tempBlock->next;
			prev = prev->next;
		}
	}
}

void removeFromFree(void *ptr) {
	struct block *tempBlock = freeHead;
	struct block *prev = tempBlock;
	if (ptr == tempBlock) {
		freeHead = tempBlock->next;
		return;
	}
	else {
		tempBlock = tempBlock->next;
		while (tempBlock) {
			if (ptr == tempBlock) {
				prev->next = tempBlock->next;
				return;
			}
			tempBlock = tempBlock->next;
			prev = prev->next;
		}
	}
}
void* newBlock(size_t s) {
  printf("allocating %zu\n", s);
  void *ptr = sbrk(0);
  size_t sizeNeeded = s >= ALLOC_UNIT ? s + sizeof(block_t) : ALLOC_UNIT;
  void *request = sbrk(sizeNeeded);
  //void *request = sbrk(sizeNeeded);
  //unable to request memory
  if (request == (void*) -1) {
    return NULL;
  }
  //create new header at start of memory given
  if (allocatedHead) {
	  printf("head was: %d\n", allocatedHead->debug);
  }
  else {
	  //printf("head was: NULL\n");
  }
  block_t* newHeader = ((block_t*)request);
  newHeader->size = s;
  newHeader->next = allocatedHead;
  newHeader->free = 0;
  newHeader->debug = counter;
  allocatedHead = newHeader;
  //printf("header allocated at %zu\n", request);
  
  //printf("head is now: %d\n", allocatedHead->debug);
  void* blockMemoryLoc = (void*)((unsigned long)request + sizeof(block_t));
  return blockMemoryLoc;
}


void printList(struct block *list) {
	struct block *tempBlock = list;
	//if (tempBlock) {
		////printf("block in list: %d\n", tempBlock->debug);
	//}
	// search linked list for Memory
	int count = 0;
	while (tempBlock && count < 5) {
		//printf("block in list: %d\n", tempBlock->debug);
		//printf("block size: %d\n", tempBlock->size);
		//printf("block free: %d\n", tempBlock->free);
		tempBlock = tempBlock->next;
		count = count + 1;
	}
}

void* mymalloc(size_t s){
	counter = counter + 1;
	//printf("MALLOC CALL: %d\n", counter);
	if (allocatedHead) {
		//printf("starting malloc. head is: %d\n", allocatedHead->debug);
	}
	//printf("allocated list:\n");
	printList(allocatedHead);
	//printf("free list:\n");
	printList(freeHead);
	//return null if size is non positive
	if (s < 1) {
		return NULL;
	}

	struct block *tempBlock = freeHead;
	// search free linked list for Memory
	while(tempBlock) {
		//printf("free exists\n");
		if(((tempBlock->size) >= s) && ((tempBlock->free) == 1)) {
			removeFromFree(tempBlock);
			//printf("can use free\n");
			tempBlock->free = 0;
			tempBlock->next = allocatedHead;
			allocatedHead = tempBlock;
			//printf("allocated list:\n");
			printList(allocatedHead);
			//printf("free list:\n");
			printList(freeHead);
			return tempBlock;
		} else {
			tempBlock = tempBlock ->next;
		}
		counter = counter + 1;
	}

	//no preallocated free memory found
	if(!tempBlock) {
		// We we are out of memory
		// if we get NULL back from malloc
		//add new block to memory.
		void* addedBlock = newBlock(s);
		if(addedBlock == NULL) {
			//printf("failed to make memory\n");
			exit(1);
		} else {
			////printf("added block size: %zu\n", allocatedHead->size);
			////printf("malloc %zu bytes\n", s);
			//////printf("returning block: %d\n", allocatedHead->debug);
			//printf("allocated list:\n");
			printList(allocatedHead);
			//printf("free list:\n");
			printList(freeHead);

			//printf("ended malloc. head is: %d\n", allocatedHead->debug);
			return addedBlock;

		}
	}
	
	return tempBlock;
	
}


void* mycalloc(size_t nmemb, size_t s){
	size_t size = nmemb * s;
	void *ptr = mymalloc(size);
	memset(ptr, 0, size);
	return ptr;
}


void myfree(void *ptr) {
	//printf("Freed some memory\n");
	//printf("allocated list:\n");
	printList(allocatedHead);
	
	// search linked list for Memory
	void *prgBreak = sbrk(0);
	struct block *tempBlock = allocatedHead;
	
	while (tempBlock) {
		//printf("currently looking at  %zu\n", tempBlock);
		//printf("currently looking for %zu\n", ptr - sizeof(block_t));
		//printf("break at              %zu\n", prgBreak);
		//printf("added point is        %zu\n", ptr + tempBlock->size);
		if (tempBlock == ptr - sizeof(block_t) && ptr + tempBlock->size == prgBreak) {
			//printf("top\n");
			removeFromAllocated(tempBlock);
			sbrk(0 - sizeof(struct block) - tempBlock->size);
			return;
		}
		else if(tempBlock == ptr - sizeof(block_t)) {
			//printf("not top\n");
			
			
			removeFromAllocated(tempBlock);
			tempBlock->next = freeHead;
			freeHead = tempBlock;
			tempBlock->free = 1;
			//printf("free list:\n");
			printList(freeHead);
			return;
		}
		tempBlock = tempBlock->next;
	}
	//printf("no allocated\n");
	
}
