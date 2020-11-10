# PThreads and Semaphores

# Introduction

<img align="right" src="./media/bolt.jpg" width="200px" alt="Usain Bolt">


One of my favorite events to participate in my competitive running days was in relay races. A typical relay race has 4 runners, each running an equal distance(e.g. 400 meters), and then passing a baton to the next runner on their team. Runners are not allowed to start running until the previous runner has finished. The first runner is the lead, and the last runner (the fourth runner) is typically called the anchor. It is important that only one runner is ever running at a given time. 

Today you are put in charge of several olympic (and former olympic) athletes who you will be coaching through a relay. Unfortunately, they are not very synchronized. Read on to the task!

## Task 1 - Help the Olympic Relay Team

You are provided a file [relay.c](./relay.c) which you will work in. 

* Compile the c program with: `gcc -lpthread relay.c -o relay` (Note that you are dynamically link in the [pthread](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html) library with -lpthread)
* Then run the compiled program with `./relay`

After you compile and run the program, you receive the following output:

```
-bash-4.2$ ./relay
Usain Bolt has taken off!
Michael Johnson has taken off
Allyson Felix has taken off
Carmelita Jeter runs the anchor leg to the finish line!
```

The above is the correct ordering of athletes, and you run the program again to verify.

```
-bash-4.2$ ./relay
Usain Bolt has taken off!
Carmelita Jeter runs the anchor leg to the finish line!
Allyson Felix has taken off
Michael Johnson has taken off
```

Hmm, this time the order is not correct! And even worse, you realize all of the runners are taking off at the same time in the relay race!

**Your task**: Correct the [relay.c](./relay.c) program using multiple semaphores to ensure that each runner runs in the correct order, and only one runner thread is executing at a given time.

## Rubric


<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>20% for Task1</td>
	    <td align="left"><ul><li>Implement the Signal Concurrency Pattern</li><li>There should be no deadlocks or data races</li></ul></td>
    </tr>          
  </tbody>
</table> 

# Resources to help

- [A simple semaphore example](http://www.amparo.net/ce155/sem-ex.html)

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Check out [The Little Book of Semaphores](https://greenteapress.com/wp/semaphores/) by Allen Downey for more on the signaling pattern.
