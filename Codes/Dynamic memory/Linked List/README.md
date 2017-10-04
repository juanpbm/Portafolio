# Linked List


This code was made in mobaXterm (linux) using C++. For this code, I worked with a partner.

The main purpose of this program is to create a list of an indefinite number of elements using liked lists; Each element is contains 
a number (person's age ) and a string (person's name ) this program shows the main menu with 7 options:

1: Append an element at the end: this option allows the user to add a new person with an age and a name at the end of the list.

2: Find a person: the user will input the index of a person he wants to find and print its name and age.

3: Remove a person: the user inserts the index of the person he wants to remove and the name and age of that person won't be on the list
anymore. 

4: Insert an element: the user inserts the index where he wants to place the new person, the name and, the age and the program will add  
the information in the desired index.

5: Print the list: the program will print all the information of the list in the form " X is Y years old" (X = name, Y = age).

6: Exit: the user selects this option to end the program. The program will run until this option is selected.

7: Sort: the program will ask the user if he wants to organize the list by name (1) or by age(2). if 1 is inserted, the program will 
organize the list in alphabetical order. if 2 is inserted the program will organize the list from the youngest to the oldest person 
on the list.

Also, there is a makefile that is a shortcut to the compilation commands. Making this fill allows us to use the command make and compile 
the code easily. One of this commands, run, allows us to use the gdb debugger in mobaXterm. 
