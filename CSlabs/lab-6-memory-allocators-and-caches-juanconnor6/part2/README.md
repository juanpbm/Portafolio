# Cache Simulator

In this part, we are going to work with two tools to help understand directly mapped caches. There will be some opportunities to play around with the source code as well!

## Trace (trace.c)

[Trace](./trace.c) is a program that generates a series of values from 0-1024. These values represent the addresses of instructions that a cpu would execute one after the other. As an example of part of a 'trace' file is displayed below:

```
...
10100101
10100101
10100101
10100101
...
```

A trace file of a program is a *log* of what happened when actually executing a program. Again--our trace file shows the series of instructions that our cpu executed. We can simulate a run of a program by generating a trace with random addresses which may be useful for understanding the behavior or efficiency of our cpu. Think of this as creating an algorithm that may represent a typical programs control flow, modeleling its data access patterns.

In [trace.c](./trace.c), I have built 4 different functions to simulate different executions of programs control flow.

1. realistic - Randomly generate addresses, but repeat them several times. This simulates 'jumping' in our code.
2. random - Randomly generate addresses.
3. single - Only one instruction is ever executed.
4. regular - A very regular data pattern where addresses cycle.

* You will compile with: `clang -lm trace.c -o trace` (The -lm brings in the math library)
* Then run: `./trace`
* After running `./trace`, several .txt files storing a simulation of our program using the above algorithms will be created.
  * e.g. Use `nl regular.txt` to view the trace, or otherwise open each .txt file in vim.

## Binary (binary.h) (For your understanding)

[binary.h](./binary.h) contains some binary manipulation functions. You should not need to modify any of this code.

The functionality provided in [binary.h](./binary.h) is the ability to select specific ranges of bits and convert that range to be used as an index or tag. A snippet is shown below:

```c
// This function can pick out a range of numbers
// That is, given the string "10000001"
//                            ^^^
//                            76543210
//           A start of 5 and a stop of 7 returns the integer 4 (i.e. 100)
int binaryStringRangeToInt(char* bin, int start, int stop){
```

## Simulator (simulator.c)

After you have generated trace files(by running ./trace), let us use them to *measure* the cache behavior of our program.

We are going to play a bit of a game with the Cache simulator! You can challenge someone next to you (or your partner), to see who can minimize the latency in the system!

The simulator provided follows the directly mapped cache mechanism, where there are 4 cache sets, each with 1 cache line and 1 block of information.

### Important parts of the source code in simulator.c.

1. Eviction and replacement policy, this is where the work is done! Note this will need to be accurate in order for your simulation to work. By default, a replace always policy is implemented.
2. There are a lot of binary conversions to string conversions. You should not need to modify those functions(unless you uncover a bug!). However, if you do extend the cache, you will need to change the indexing scheme to accommdate it appropriately.
3. There are costOfMiss and costOfHit variables that relate to how much latency each has. 
    - You should keep these consistent if you are comparing with someone next to you.

* You should compile simulator with: `clang -std=c11 -lm simulator.c -o simulator`
* You should then run the simulator and feed it a trace that has been generated: e.g. `./simulator realistic.txt`

## Your Task

Your task will be to add two new functions in [trace.c](./trace.c) to create two new .txt traces that demonstrate:

1. One program that is cache unfriendly (any trace that when run has more misses than hits)
2. One program that is cache friendly (any trace file that runs has more hits than misses)

Think about this means when generating the instructions, and use the previously provided functions as inspiration.

## Lab Deliverable

1. (20 points) Add another trace that is very cache friendly(i.e. more hits than misses) and commit the .txt to the repository.
2. (20 points) Add a trace that is very unfriendly (adverserial, more misses than hits) to cache systems and add the .txt to the repository.

## More Resources to Help

* What is a CPU Cache https://www.youtube.com/watch?v=sHqNMHf2UNI (0:00 - 3:55)
* Why do CPUs need Caches - Computerphile https://www.youtube.com/watch?v=6JpLD3PUAZk

## Going Further

#### Tasks to try (Optional)

1. Keep track of what kind of cache misses occur (cold, capacity, or conflict)
2. Our cache is very small--could you increase the number of cachelines?
3. What happens if you shrink the cache any smaller?
4. Could you add an additional block in our cache to make use of the block offset?
5. Try running a bigger simulation (will require modifying trace), to run 4096 addresses.
6. Output a percentage of the cache misses.
7. Create a cache policy where you put something randomly in the cache. This means you have to scan all of the cache lines (Which costs on the latency).

#### Thoughts on ways to improve caching.

1. Make the cache really big (okay this is a cheat, but you can explore just to see on the various traces.
2. The 'block offset' bit is currently not used. Try adding an additional block. This will require several changes however (extending the cache lines), make sure you understand the code base first!

#### Investigate this cache simulator
* http://www.ecs.umass.edu/ece/koren/architecture/Cache/frame1.htm
