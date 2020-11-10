In a brief sentence or two,  modify this file with your answers.

1. In each of the programs what was the bug?

Prog: The bug is a segmentation fault

Prog1: The bug is a segmentation fault

2. What file and lines did the bugs occur?

Prog: The bug occurred in the file Prog2.c in line 57

prog1: The bug occurred in file seg.c in line 15

3. What would your educated guess be for a fix for each bug? 

Prog: The program is trying to access a location in the memory that is empty. Maybe at some point, this memory location (maybe a pointer) was freed or it's trying to access the wrong location.  

prog1: the program is trying to manually assign an address to (%rax) maybe this address is already being used and the program doesn't have permission to modify it. 
