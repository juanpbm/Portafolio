# Linked List


This code was made using mobaXterm (linux) using C++ in collaboration with a partner.

The main purpose of this program was to create a list of an indefinite number of elements using liked lists; Each element contained 
a number (person's age ) and a string (person's name ). This program displayed the main menu with 7 options:

1: Append an element at the end: this option allowed the user to add a new person with an age and a name at the end of the list.

2: Find a person: the user gave the index of a person to find and the code printed the name and age.

3: Remove a person: the user gave the index of the person to remove and the name and age of that person would be deleted from the list. 

4: Insert an element: the user gave a new index to assign a new entry, in addition to an age and a name, and the program would add the information accordingly.

5: Print the list: the program printed all the information of the list in the form " X is Y years old" (Where X = name, Y = age).

6: Exit: the user selected this option to end the program. The program would run until this option was selected.

7: Sort: the program would ask the user if the list should be organized by name (1) or age (2). If 1 was selected, the program would 
organize the list in alphabetical order. if 2 was selected, the program would organize the list from the youngest to the oldest person 
on the list.

Additionally, there would be a makefile that serves as a shortcut to the compilation commands. Making this would allow the use of the command "make" to compile the code with ease. One of this commands, run, allowed the use of the gdb debugger in mobaXterm. 
