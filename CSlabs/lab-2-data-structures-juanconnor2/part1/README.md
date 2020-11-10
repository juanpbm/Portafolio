# Building Data Structures - Queue
<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/450px-Data_Queue.svg.png" alt="Queue picture">

We have previously learned the Linked List Data Structure. Now we will introduce another data structure, known as the 'queue'.

A 'queue' data structure is analogous to waiting in line at a grocery store. The first person to the checkout counter is served, followed by the next person, and then the next until the line is empty. A queue is what is known as a 'first-in first-out' (FIFO) data structure. Thus queues have a strict policy about how information is stored and accessed.

For this assignment, you are going to implement a specific implementation of a queue using an array in the [myqueue.h](./myqueue.h) file. This data structure is also called a circular queue (specifically a ring buffer when the maximum storage size is fixed).

## Circular Queue (Ring Buffer) implementation using an array.

A circular queue has a fixed sized, or maximum number of elements that it can hold. This is advantageous if we know how many elements are typically stored in a data structure (If we do not know, then a queue with a linked list implemetation is needed). 

For more information on the Circular buffer, see here: https://en.wikipedia.org/wiki/Circular_buffer

This animation below gives an idea about how the data structure 'wraps' around. Think about what mathematical operator has a *wrap around behavior* that could be useful in your implementation when enqueuing and dequeuing items in your queue (*hint* this operator will save you from writing many if-statements in your code!).

![](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Circular_Buffer_Animation.gif/400px-Circular_Buffer_Animation.gif)

**Your task** will be to implement the functions in the [myqueue.h](./myqueue.h) to have a working implementation of queue.

## What is a file that ends in .h.

A file that ends in .h is known as a header file. A header file typically is a file that contains an 'interface' for a set of functions to perform some task. The actual implementation (i.e. the loops, if-statements, arrays, and tools that do work) are found in a .c file. 

For this assignment, our 'queue' library is quite small, so we will implement the entire functionality into a header file. There are some pros and cons to this approach. One particular 'pro' is it makes your code very easy to test. We will simply use our own 'main.c' file to test your implementation (that is why it is important you do not change the names of any functions). 

* More information on header files
	* https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html

## Why is a ring buffer/circular queue useful?

Circular queues are used quite a bit in operating systems and high performance systems, especially when performance matters. Do a little outside research, and edit this section of the readme answering specifically: Why is a ring buffer useful and/or when should it be used?

# TODO: Put your answer here

All operations of a queue are O(1) as there are no loops, so it is very fast and efficient. It is best used in scheduling tasks, or preparing events in FILO (first in last out) ordering when the size needed is known. For example, operating systems use queues for CPU scheduling to maintain a queue of processes or events that are waiting to be run. 

Circular queues should not be used when storage is a constraint, and storage is highly variable. To resize a circular queue, a new one must be reconstructed which can be a big hit to performance. It also should not be used if random access is needed, as elements would need to be dequeued then enqueud once again which isn't efficient. 


# Unit Tests

A unit test is a standalone test that checks for the correctness of a specific use case in your code. In our case, we are testing if we have a working queue implementation. A sample unit tests is given:

```c
void unitTest1(){
	queue_t* test1 = create_queue(1);
	printf("Attempting to add %d\n",1);
	queue_enqueue(test1,1);	
	printf("Removing: %d\n",queue_dequeue(test1));	

	free_queue(test1);
}
```

You *may* also consider writing some unit tests to test your implementation (In fact, I would strongly encourage you to do so). Note that you can include your unit tests in your submission, and we will have our own test suite. Some example tests we might come up with include:

* Fill a queue, empty the queue, and fill the queue again.
* Create an empty queue and attempt to add something to it.
* Make sure your queue does not overwrite any data.
* etc.

## Provided Tests

You are provided a file called queue_test.c which you can compile separately and test your implementation of your queue functions from your header file. Doing so does not guareentee a perfect assignment, but it will give you some confidence your implementation is working.

* Compile: `gcc queue_test.c -o queue_test`
* Run: `./queue_test`

# Rubric

* Your implementation will be graded by our set of unit tests, and we will check your code 'style' as well.

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>25% (Queue Implementation)</td>
      <td align="left"><ul><li>All functions should be implemented.</li><li>You did not rename any functions (but you may add any 'helper' functions if you deem necessary--e.g. queue_print)</li><li>There should be no memory leaks</li><li>There should be no bugs in your functions </li></ul></td>
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
- [https://en.wikipedia.org/wiki/Queue_(abstract_data_type)](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
	- Queue Data Type High level description
  
# Going Further
(An optional task to extend this assignment--not for bonus, but just for fun)

* Add additional functions like:
  * queue_peek - Returns the first value in the queue
  * queue_back - Returns the last value in the queue
  * queue_equals - Checks if two queues are equal
  
  
* Information on pros/cons of our header only design
	* https://softwareengineering.stackexchange.com/questions/305618/are-header-only-libraries-more-efficient
* Some examples (Revisit this again in a few weeks)
	* https://github.com/nothings/single_file_libs  
  
# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Investigate/Review more data strutures on this webpage: https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
  - There are visuals for the linked list and array based queue here!
  - Use them as a *rough* guide for the basic concepts. Do make sure to follow the specifications for our assignment above.

