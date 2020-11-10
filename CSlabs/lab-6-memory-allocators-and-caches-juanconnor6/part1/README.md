# Allocator

**TODO/EDITME** Check only one box for which allocation strategy you implemented (This helps the TAs with grading, we'll figure it out if you forget.)

- [x] First-Fit
- [] Best-Fit allocator

Other notes: *If you did anything above and beyond, or want to leave a TA a note you may do so here.*

# Introduction - Memory Allocator 

In this part, you will be writing your own memory allocator! Writing a custom memory allocator is something you might do, especially if you work on any performance sensitive system (games, graphics, quantitative finance, embedded devices or any an application you want to run fast!). [Malloc](https://linux.die.net/man/3/malloc) and [Free](https://linux.die.net/man/3/free) are general purpose functions written to manage memory in the average use case quite well, but they can always be optimized for a given workload further (aside: a lot of smart folks have worked on making malloc/free quite performant!). And optimization aside, you might simply write an allocator to add in cool debugging features, and swap it in as needed.

For this assignment, we will implement a portion of a custom memory allocator for the C language. This includes writing:

- [malloc](https://linux.die.net/man/3/malloc)
- [calloc](https://linux.die.net/man/3/calloc)
- [free](https://linux.die.net/man/3/free)

## Task 1 - Memory Allocator 

### Design Decisions

Your objective will be to create three functions in [mymalloc.c](./mymalloc.c)

1. malloc
2. free
3. calloc 

Please read through the following design decisions to help guide you. This is some of the thought process a designer of such a system may go through. I provide more concrete specifications below.

#### Decision 1 - How to request memory?

Remember that malloc,calloc, and free are all working memory allocated on the heap. We can request memory from the operating system which is resonsible for giving us memory when we use a system call such as [sbrk](https://linux.die.net/man/2/sbrk). There exists other ways to request memory such as [mmap](https://linux.die.net/man/3/mmap) that you will have to use for your next assignment.

So for now, we will request memory through the sbrk system call.

#### Decision 2 - How to organize our memory?

Once you have retrieved memory, we need to keep track of it. That means that everytime a user uses your 'malloc' or 'calloc' functions, you will want to know where that memory exists, and how big it is. Thus, we want to keep track of all of the memory we request in a convenient data struture that can dynamically expand.

So think about: What data structure should I use?

#### Decision 3 - What else will I need?

You may define any helping data structures and functions that assist you in this task. This means you might even have a global variable or two to assist with your implementation. Depending on what data structure you decide to store all of the requested memory in, it may be useful to have additional helper functions for traversing your data structure and finding free blocks/requesting blocks for example.

#### Decision 4 - How will I efficiently reuse memory already allocated on the heap?

Programs may frequently allocate and then free memory throughout the programs execution. It can thus become expensive to keep expanding the heap segment of our process. Instead, we try to reuse block as efficiently as possible. That is, if I have allocated a block of memory of 8 bytes, and that 8 bytes gets freed, the next time I call malloc I can use the previous 8 bytes without having to make another call to sbrk or mmap. There exist at least two algorithms for allocating memory:

1. Best-fit - This tries to find an 'optimal size' of a previously freed block to place memory in.
2. First-fit - This finds the first block of memory that will fit the request.

Each strategy has a trade-off of performance vs fragmentation. For example, it may take longer to find an optimal sized block, but that will likely lead to less fragmentation. 

For this assignment, you can choose to implement either a best-fit allocator or a first-fit allocator.

### Concrete Specification for your alloactor.

Let me provide you with some default specifications to get everyone on equal footing. You are welcome to diverge if you think you can build something more optimal, but I recommend getting this basic allocator with the specifications below to work first!

1. You should have a linked list data structure. 
	- This data structure will keep track of the blocks that you have allocated within your malloc function. 
	- You should have a global variable that serves as the "head" or "first block of memory" in your linked list.
	- You should have some notion of a 'block' of memory in your program.
	- An example is provided here with some fields that may be useful:
	```c
	  struct block{
	    size_t size; // How many bytes beyond this block have been allocated in the heap
	    block* next; // Where is the next block in your linked list
	    int free; // Is this memory free?
	    int debug; // (optional) Perhaps you can embed other information--remember, you are the boss!
	  };
	```
2. You will want to keep track of how big this block structure is. A little trick is to use the preprocessor so you can simply use BLOCK_SIZE in your code.
	```c
	#define BLOCK_SIZE sizeof(block)
	```
3. The [sbrk](https://linux.die.net/man/2/sbrk) command will be your friend. Understand what sbrk(0) does and sbrk(10) before getting started. Your malloc function (or helper functions) are what will use malloc.
4. Your free function can be as simple as setting a block of memory to be free. Consider how memory is laid out in the heap however to make sure you are only accessing your struct. Here is a simple diagram: 
```
|block|----actual memory----|block|--------actual memory-------|block|--actual memory--|

  ^ Here is where your struct lives, this is what you want to update.
```
5. Your `calloc` function(mycalloc) can make a call to your malloc function (mymalloc). 
	- Remember what is different about calloc however!
6. A first-fit memory allocator means, we are looking for any block in our linked list that is free (any previously allocated blocks that is). Remind yourself what the trade-off is between the other allocators (e.g. compare to a 'best-fit' allocator).
	- A best-fit allocator (which will earn full marks on this assignment) scans through a list and finds the optimal position to minimize external fragmentation.
	- You may have a heuristic that finds blocks that are up to 4 bytes bigger that can be used.
		- (Otherwise, if there is no optimal block, you must request more memory with sbrk).
7. Your malloc function(mymalloc) should print out "malloc %zu bytes\n"
8. Your calloc function(mycalloc) should print out "calloc %zu bytes\n"
9. Your free function should print out "Freed %zu bytes\n"
10. With these print outs, you can see if they match the original programs.
11. I will look through your code to make sure you do not use the C library malloc/calloc/free from <stdlib.h>. You should only be using syscalls such as sbrk (you may also use mmap if desired) to request memory from the operating system.

## How to run the assignment.

A [compile.py](./compile.py) file and [run.py](./run.py) file is also provided for you.

1. First run [compile.py](./compile.py) to make sure everything builds by default with: `python compile.py`
2. Then run [run.py](./run.py) to make sure everything runs ([run.py](./run.py) also compiles the code): `python run.py`
3. You will notice in the tests directory, some small tests have been created for you. 
	- test1, test2, etc. use the default implementation of malloc. 
	- test1_mymalloc, test2_mymalloc, etc. use your custom implementation of malloc and free. 
	- You will notice in the compile script, the use of compile-time interpositioning to replace the default C memory allocator with your own is done.
4. Okay, now you are ready to begin implementing malloc, calloc, and free. Some details on the specifications are below.

# Rubric

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>10 points for good programming style</td>
      <td align="left"><ul><li>Did you break your code into functions that are < 50 lines.</li><li>Are you using lots of globals? (Note: It *may be okay* to use a few for an allocator)</li></ul></td>
    </tr>
    <tr>
      <td>30 points for a working memory allocator(i.e. mymalloc/mycalloc/myfree)</td>
      <td align="left"><ul><li>You can implement either a working first-fit allocator that does not leak memory OR a working best-fit allocator that does not leak memory.</li></ul></td>
    </tr>    
  </tbody>
</table> 

    
# Resources to help
- Advanced Material: https://www.youtube.com/watch?v=kSWfushlvB8 ("How to Write a Custom Allocator" for C++)
- The book Programming in C (K&R book) has a nice description of memory allocators.

# F.A.Q.

Q: Do I have to reduce the heap ever?
A: No, you do not need to ever make calls to sbrk(-10) for example.

Q: Can I use valgrind to check for memory leaks in my program?
A: Likely not, because you are implementing your own allocator. Valgrind may not be able to track calls to sbrk (or mmap) reliably. There exists an interface to do this, but that is probably a research project for next semester!

Q: How will I know my tool is working?
A1: This is a pretty general question, but a tool like strace can be helpful. strace can be run on the tests once you have compiled them. strace can report how many calls you have made to 'brk' for example, and you can test your assumptions to see if that system call is being made too often (i.e. not reusing blocks that have been previously allocated and could be used).

A2: You could also run your allocator with your linked list or other data structures and see if it passes the unit tests.

# Going Further

- You do not have to align your memory, but you may choose to (I will only run test on nicely sized memory blocks).
- Blocks of memory typically are aligned. That is, they are aligned to some address boundary (every 8, 16, 32, 64, etc.). In order to make our memory allocator more simple, we can force alignment of every block. Here is a trick using a union from the K&R book.

```c
typedef long Align; // Alignment to long size

union header{
  struct{
    union header *ptr;  // next block in free list
    unsigned size;      // Size of this block
  } s;
  Align x;  // Force alignment of blocks to our boundary.
            // Note this field is never used, but space is allocated for it.
            // Convince yourself this 'trick' works and why.
};
```


Other Notes:

* In order to avoid fragmentation, most allocators combine blocks that are adjacent(on both sides) into bigger ones. They may then split those bigger blocks as need as well. You could write some helper functions to assist with this, and have a more optimal memory allocator. 
	- This is optional for this assignment.
* The malloc implementation is actually open source, so you can take a look at it if you are curious.

