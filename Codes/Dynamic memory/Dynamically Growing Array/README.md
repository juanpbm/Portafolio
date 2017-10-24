# Dynamically growing array

This code was made in mobaXterm using C++ in collaboration with a partner. 

This code was made to allow the user to create an array for an indefinite number of elements.
This program displayed the main menu with 7 options:

1: Append an element at the end: this option allowed the user to add an elememt at the end of the array.

2: Print the array: the program printed all the information of the array.

3: Remove an element: the user gave the index of the element to remove and that particular number would be deleted from the array and move every other element one space to the left.

4: Insert an element: the user gave a new index to assign a new entry, and the program would add the information accordingly and move every other element one space to the right.

5: Exit: the user selected this option to end the program. The program would run until this option was selected.

If option 1 or 4 were selected, the program would check available space in the array to add a new element. In the event of not enough space being available, the array would be doubled in size. Moreover, in option 3, upon deleting an element, the program would shrink the array by half the size if less than 30% of the total capacity were occupied. 

