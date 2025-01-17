# Building Data Structures - Stack
<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b4/Lifo_stack.png/350px-Lifo_stack.png" alt="Stack picture">

A 'stack' data structure is analogous to how you might wash dishes at a restaurant. A dirty dish is placed near the sink, and you pick it up to begin washing it. As customers bring in more dirty dishes, they are stacked on top of each other. With this ordering, the newest dirty-dish is placed on the top. This makes a stack a  'last-in first-out' (LIFO) data structure. Thus stacks have a strict policy about how information is stored and accessed.

For this assignment, you are going to implement a specific implementation of a stack using a linked list in the [mystack.h](./mystack.h) file.

## Stack implementation using a linked list.

Our stack has two fundamental operations that it can perform:

1. push - Add elements to the top of the stack.
2. pop  - Remove elements from the top of the stack.

You will notice, both of these operations happen at *the top of the stack*. Sometimes, we also refer to these operations as 'enqueue' or 'dequeue' so we have a consistent langauge for our data structures.

Our stack that we are implementing can expand dynamically, thus a linked list is a good foundational data struturre to use in our implementation.

Our stack can push elements onto it, until `MAX_DEPTH` is reached. MAX_DEPTH is defined as 32 for our implementation. For our implementation, we are artificially setting this limit. Remember however, we only have a finite amount of memory on our systems, so if we had very large stacks, we could get a [stack overflow](https://en.wikipedia.org/wiki/Stack_overflow).

For more information on the stack, can be seen here: https://en.wikipedia.org/wiki/Stack_(abstract_data_type)

**Your task** will be to implement the functions in the [mystack.h](./mystack.h) to have a working implementation of stack.

## What is a file that ends in .h.

A file that ends in .h is known as a header file. A header file typically is a file that contains an 'interface' for a set of functions to perform some task. The actual implementation (i.e. the loops, if-statements, arrays, and tools that do work) are found in a .c file. 

For this assignment, our 'stack' library is quite small, so we will implement the entire functionality into a header file. There are some pros and cons to this approach. One particular 'pro' is it makes your code very easy to test. We will simply use our own 'main.c' file to test your implementation (that is why it is important you do not change the names of any functions). 

* More information on header files
	* https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html

## Why is a stack a useful data structure?

We are going to talk about stacks quite a lot in this course, so it will be important to understand them. Do a little outside research, and edit this section of the readme answering specifically: Why is a stack useful and/or when should it be used?

# TODO: Put your answer here

A stack is a linear data structure with LIFO behavior (Last In, First Out). This means that a new item is always added at the beginning of the stack and the first item is the first to be removed. The complexity of a stack in the worst case is O(1). This makes the run-time less than when other data structures are used. Stacks are mostly used by the OS to process nested structures, functions or keep track of variables. They help to order all the steps the OS have to follow to run a program.

The main problem of this data structure is that it doesn’t allow random access. You can’t access an element that is not in the first position, first all the previous elements must be removed. Also, there is a limit, if too many elements are added there can be a stack overflow and the program will crash. On the other hand, not being able to randomly access the data gives you security preventing from overwriting data. Moreover, when variables are created the OS adds them to a stack and deletes them when they are no longer needed. This helps you clean up and you don’t have to manually free the space of every single variable.

# Unit Tests

A unit test is a standalone test that checks for the correctness of a specific use case in your code. In our case, we are testing if we have a working stack implementation. A sample unit tests is given:

```cpp
void unitTest1(){
	stack_t* test1 = create_stack(MAX_DEPTH);
	printf("Attempting to add %d\n",1);
	stack_enqueue(test1,1);	
	printf("Removing: %d\n",stack_dequeue(test1));	

	free_stack(test1);
}
```

You *may* also consider writing some unit tests to test your implementation (In fact, I would strongly encourage you to do so). Note that you can include your unit tests in your submission, and we will have our own test suite. Some example tests we might come up with include:

* Fill a stack, empty the stack, and fill the stack again.
* Create an empty stack and pop an item to add something to it.
* etc.

## Provided Tests

You are provided a file called queue_test.c which you can compile separately and test your implementation of your queue functions from your header file. Doing so does not guareentee a perfect assignment, but it will give you some confidence your implementation is working.

* Compile: `gcc stack_test.c -o stack_test`
* Run: `./stack_test`

# Rubric

* Your implementation will be graded by our set of unit tests, and we will check your code 'style' as well.

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>35% (Stack Implementation)</td>
      <td align="left"><ul><li>All functions should be implemented.</li><li>You did not rename any functions (but you may add any 'helper' functions if you deem necessary--e.g. stack_print)</li><li>There should be no memory leaks</li><li>There should be no bugs in your functions </li></ul></td>
    </tr>
    <tr>
      <td>5% (Writeup)</td>
      <td align="left"><ul><li>Correct writeup on the importance of queues/ring buffers as related to OS</li><li>I expect this to be in the range of 2-3 paragraphs (Can include complexity, example usage, pros/cons, etc).</li></ul></td>
    </tr> 
  </tbody>
</table>

# Resources to help

- [http://www.learn-c.org/](http://www.learn-c.org/) 
	- This is a nice interactive tutorial for learning C
- [https://en.wikipedia.org/wiki/Stack_(abstract_data_type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
	- Stack Data Type High level description
  
# Going Further
(An optional task to extend this assignment--not for bonus, but just for fun)

* Add additional functions like:
  * stack_peek - Returns the top value of the stack (without removing it)
  * stack_equals - Checks if two stacks are equal
  
  
* Information on pros/cons of our header only design
	* https://softwareengineering.stackexchange.com/questions/305618/are-header-only-libraries-more-efficient
* Some examples (Revisit this again in a few weeks)
	* https://github.com/nothings/single_file_libs  
  
# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Investigate/Review more data strutures on this webpage: https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
  - There are visuals for the linked list and array based stack here!
  - Use them as a *rough* outline for the genearl concept. Do make sure to follow the specifications above.

