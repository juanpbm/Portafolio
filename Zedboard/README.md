# OOP controlling the ZedBoard

The objective of this project was to control a ZedBoard and create a code using object-oriented programming to simplify the task of controlling it in the future. The ZedBoard (http://zedboard.org/product/zedboard) has 8 LEDs, 8 switches, and 5 Buttons. 


## Walter Galdamez and Juan Pablo Bernal

# Controlling individual LED states

The goal of this part was to turn on and off the LEDs of the ZedBoard depending on the user input (index of LED and state 1 or 0). The code for this part can be found in the folder led  

1.) To solve this part of the problem, we created a switch statement that took in the index of the LED's as each case. The indexes went from 0-7 because there are 8 LED

2.)Inside each case, we then made a function call to the function RegisterWrite(ptr,gpio_led1_offset,state) which took the pointer of the memory address, the memory address of the LED and the state 0 or 1, which the user inputs. 0 means 0ff and 1 means on.

3.) After the function call finishes, the program terminates. We created an infinite loop to repeat the prompt window to show that we successfully could control each individual LED

4.) This video here shows the how program worked: https://www.youtube.com/watch?v=AmL2EtHQu0o

# Controlling Switches 

The goal of this part was to use the 8 switches to control the 8 LEDs (turn them on and off). The code for this part can be found in the folder switch.

1.) To control the switches, we created different if else statements that read whether each individual switch was on or off. 

2.) To read whether the switch was on or off, we made a function call to the function RegisterRead() which return the value 0 or 1. If the function returned 1, other words if RegisterRead()==1, then we made that specific LED to turn on through the RegisterWrite. Else we made the LDE set to off through the same function with the state set to 0 instead of 1.

3.) Once again, we created an infinite loop to constantly update when changed the state of the switch.

4.)The video here shows that our program worked: https://www.youtube.com/watch?v=F3NLNOPGVA8

# Controlling the Push Buttons 

The goal of this part was to use the push buttons in the ZedBoards and perform some different tasks:

Center: it would set the LEDs to the state of the switches transform that number from binary to decimal and set the counter to the value (this would be done the first time the program runs).

Up: it would increase the counter by one, and set the LEDs to that value in binary form. 

Down: it would decrease the counter by one, and set the LEDs to that value in binary form.

Left: it would move the LEDs state one position to the left.

Right: it would move the LEDs state one position to the right.

the code for this part can be found in the folder push_button.

1.) To solve this part of the lab, we first created global variables for each button that were initialized as 0; we also created a global variable for the counter that was also initialized to zero.

2.) Inside the function PushButtonToLed(), we created five different variables for each button that read the state of the button when is pressed down through the function registeRead

3.)We also initialized 8 different variables to zero for the LED's that will be used to calculate the counter value.

4.) We then created the if statement if ((new_statec!=statec && new_statec == 1) || counter == 0 ) which basicallt tells the program to excute what is inside the if the center button is pressed or if its the first time the program runs .

5.) Once inside the if statement, we created another series of if-else statements that read the state of the switches which we used to match the state of LED. Then we changed the LED variables described in step 3 to the corresponding state of the LED. For instance, if LED state is 1 then Led1=1.

6.) After, we used these LED variables to calculate the counter using conversion from binary to decimal. Basically, raising each LED state by consecutive powers of two. The first LED state is 2^(0) times the LED state + 2^(1) times the LED state.....2^(7) times the last LED states.

7.)Finally, we created another set of if statements for the buttons. The if the statements were constructed like this if (new_stateu!=stateu && new_stateu == 1) which basically means that when we push the button, we are changing the state of that button, therefore, new_stateu!=stateu because new state equals 1 while state equals zero. 

8.)Inside the if statement we changed the counter depending on the button. For instance, the up button increases counter by one, the down button decreases counter by one, the left button shifts the counter one bit to the left, the right button shifts the counter one bit to the right, and the center button resets the LED to the original counter.

9.)This video shows how it works: https://www.youtube.com/watch?v=sSEf75b6LxY

# Using C++ objects 

The goal of this part was to do the first part again but now using object oriented programming. The code for this part can be found in the folder class.

1.) We created a .h file named Zedbaord that contain the definition of a class called ZedBoard and all the variables for the memory address in the private section. These variables were later initialized in the constructor of this class. Also, this class contained all the functions, like RegisterWrite and read, and SetLedByValue. Basically, the .h file was used to initialize all the needed variables and functions.

2.)In the zedboard.cc we developed all the functions that were declared in the .h file. The functions were defined as defined in the .h file.

3.) Then in the main.cc, we created an object zb that was a member of the class Zedboard. Finally, we accessed the function SetLedByValue through the command zb.fuction name. And terminated the program after this.




