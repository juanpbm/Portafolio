# Dynamically growing array

This code was made in mobaxterm using C++. For this code, I worked with a partner. 

This code was made to use allow the user create an array of an indefinite number of elements and allow to append an element at the end, insert an element,
remove an element or print the array. First, the user gets the main menu where an option can be selected. 
If the option selected is append an element at the end, the program first will check if there is enough space in the array to append the new element if there isn't enough the array will be doubled in size. If there is space, only the element will be added at the end.
If the option selected is inserted an element, the program will ask the user the index where he wants to place the new element and the new element, then place it in the desired index and move all the other values one space to the right. Again if there is not enough space the size of the array will be doubled.
If the option selected is removed an element, the program will ask the user for the index of the element he wants to remove, delete that element and move all the values one space to the right. If the number of elements in the array is less than 30% of the total capacity the array will be shrunk to the half of its previous capacity.
If the option selected is print, the program will print all the elements in the array.
Finally, this program will run until the option Exit is selected.
