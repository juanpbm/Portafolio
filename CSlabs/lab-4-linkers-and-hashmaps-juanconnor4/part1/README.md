# Compiler Interpositioning

# Introduction

For this assignment, you will be making use of the compiler to insert some instrumentation into existing functions. The general technique is known as 'interpositioning' This is related to the LD_PRELOAD trick you will have seen in lab in that we are modifying the behavior of a users source code, except this time we are only using the compiler.

# Linkers

## One more experiment on Linkers, this time with C++!

Now we have not used C++ in this course thus far, which adds various features like [function overloading](https://en.wikipedia.org/wiki/Function_overloading) (i.e. the ability to create two or more functions with the same name). And we have learned that linkers will complain if 'names' are the same, because that will result in ambiguity. So how do languages implement this feature?

### Example 1

1. Compile the program below with g++ and the `-g` with `g++ -g -c hello.cpp`.  This time we are using the gnu c++ programming language compiler instead of the C compiler. 
2. Run `objdump -t hello.o` 

Answer the first two questions in [exercises.md](./exercises.md)

```c
// filename: hello.cpp
// compile with: g++ -g -c hello.cpp
// Investigate with:  objdump -t hello.o 
int foo(int a, int b){
	return a+b;
}

int main(){

	foo(1,2);	

	return 0;
}
```

### Example 2

Languages like C++, Java, and many others have implemented a feature called templates as well. This allows us to write one version of a function and reuse it with many different data types. Take a look at the code below and try to run it. Then carefully run the same experiment and answer question 3 in [exercises.md](./exercises.md)

```c
// filename: generic.cpp
// compile with: g++ -g -c generic.cpp
// investigate with: objdump -t generic.o
template <class Datatype>

double add_generic(Datatype a, Datatype b){
	return a+b;
}


int main(){
    
    add_generic(1,1);
    add_generic(2.0f,2.0f);
    add_generic(3L,3L);
    add_generic(false,true);


    return 0;
}
```


## Compiler Hooks

With our linker trick from lab, we have replaced an existing function that we knew about (or could otherwise decipher if we have additional debugging information). (**Another word of caution** never distribute commercial software compiled with the debugging symbols.)

However, we have learned that compilers at some point have to touch every part of our source code. They are after all, responsible for compiling all of the code we have available! This can make them quite powerful tools, especially if we want to instrument programs and uncover more information. The term *instrument* here means to add additional functionality not originally in a given function.

The GCC Compiler in particular has some neat compiler hooks specifically for instrumentation. These *hooks* allow us to add in our own functions and probe a programs behavior.

### Getting setup

1. Navigate to the `trace/` folder with `cd trace/` in your terminal.
2. Within it, you will see two files [main.c](./trace/main.c) and [trace.c](./trace/trace.c). Both are quite small, investigate them now.
	- What you will see in the [trace.c](./trace.c) is some oddly named functions--two to be exact. 
	- Each of these functions has an attribute marked on them to not be instrumented (__attribute__((no_instrument_function))
). This notation is specific to the gcc compiler. 
	- Why that is the case? Well, these functions are going to be called at the start and end of every other function in our source code. 
	- That is, our compiler will automatically inject these functions into every functions body 

### Performing the instrumentation

1. First compile our main program in the trace folder: 
	- `gcc -finstrument-functions -g -c -o main.o main.c `
   	- We have passed an additional flag that leave 'stubs' for our instrumentation with the `-finstrument-functions` flag.
2. Next, let us compile our trace file: 
	- ` gcc -c -o trace.o trace.c `
3. When we have both of our object files(main.o and trace.o), we can then compile them into a single executable binary:
	- `gcc main.o trace.o -o main`
4. Finally, run `./main ` and observe the output.

## Your task

1. Our goal is to monitor some properties of [main.c](./trace/main.c) -- that is the file we are going to instrument.
2. Modify the [trace.c](./trace/trace.c) program to count the total number of functions called.
	1. Your program will print out how many total functions were called at the end of programs execution
		- You may use a global variable 
		- (Name it something like slightly more obscure like `__FunctionsExecuted__` that would be unlikely to be used by another programmer)	
3. Next, modify [trace.c](./trace/trace.c) to record how much time is spent executing the entire program.
	1. Start by investigating the C standard library [time.h](http://www.cplusplus.com/reference/ctime/).
		- A sample [difftime.c](./supplement/difftime.c) is provided for you.
	2. Use the time functions to calculate the total run-time of your program and print out the total elapsed time of your program when it finishes.
		- Note, if your time returns '0', it may be because there is so little work to do, and the computer is so fast '0' is returned. 
		- Think about adding more work to some test functions, and investigating different resolution timers.
	3. In order to compute the total elapsed time, you may use a global variable.
		- The variable must be in [trace.c](./trace/trace.c) (encapsulating all of the instrumentation in one file).
		- Think about how you can tell when to start recording time.
			- Is there some relation to the number of functions you have executed?
			- Can capturing the address of this function and storing it be useful when you exit a function?
			- Do the this_fn and call_site parameters have any meaning? Hmmm--remember everything in our programs has an address (Functions we simply have marked as labels in assembly after all)!
	4. (Optional) As a fun experiment, you may search or use your previous C assignments to profile how many times your functions execute and how many seconds it takes to execute each function.
4. Commit your new [trace.c](./trace/trace.c) file to the repository.
5. (Optional) you can print out the address of each function calling each other (demonstrated below)

### A sample of correct output for Part 2

A sample of your assignment may look similar to the following.

```shell
-bash-4.2$ ./main
        Function entered 0x4005ff from 0x7fa6f884b445
        Function entered 0x4005cd from 0x40062c
Hello!
        Function 0x4005cd exited from 0x40062c
        Function entered 0x4005cd from 0x40062c
Hello!
        Function 0x4005cd exited from 0x40062c
        Function entered 0x4005cd from 0x40062c
(more)
Total Functions called = 11	    // Your output includes # of functions called and total time.
Total Elapsed Time = 5.1242 seconds // Note: This time value may vary!
(more)
```

# Rubric
 	
<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>10% (exercises)</td>
	    <td align="left">Answer the questions about the linker in <a href="./exercises.md">exercises.md</a></td>
    </tr>	  
    <tr>
      <td>30% (Compiler Hooks)</td>
      <td align="left"><ul><li>Did you commit your trace.c with the following:</li><li>Do you successfully report the number of functions that execute?</li><li>Do you successfully report the total run-time for your program to execute?</li></ul></td>
    </tr>
  </tbody>
</table> 


# Resources to help

- Compiler Hooks https://balau82.wordpress.com/2010/10/06/trace-and-profile-function-calls-with-gcc/
- Measuring time intervals: http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html

### Glossary and Tips
1. Commit your code changes to the repository often, this is best practice.
2. Do not commit your .o file or your executable file to the repository, this is considered bad practice!


# Going Further

- [Name Mangling](https://en.wikipedia.org/wiki/Name_mangling)

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- What you have just written is a very primitive profiler. Tools like 'perf' are more powerful profilers used in industry. Using profilers can be useful for monitoring time, number of functions executed to help find where to tune performance in programs. Profilers can also scale to measure things like energy consumption at a large data center. Perhaps you will be a performance engineer one day!
