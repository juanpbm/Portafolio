#include "ZedBoard.h"
#include <iostream>
using namespace std;


void ZedBoard::SetLedByValue(int value){

                RegisterWrite(ptr, gpio_led1_offset, value % 2);
                RegisterWrite(ptr, gpio_led2_offset, (value / 2) % 2);
                RegisterWrite(ptr, gpio_led3_offset, (value / 4) % 2);
		RegisterWrite(ptr, gpio_led4_offset, (value / 8) % 2);
                RegisterWrite(ptr, gpio_led5_offset, (value / 16) % 2);
                RegisterWrite(ptr, gpio_led6_offset, (value / 32) % 2);
                RegisterWrite(ptr, gpio_led7_offset, (value / 64) % 2);
                RegisterWrite(ptr, gpio_led8_offset, (value / 128) % 2);



}

int ZedBoard::RegisterRead(char *ptr, int offset){

                return *(int *)(ptr + offset);



}
void  ZedBoard::RegisterWrite(char *ptr, int offset, int value){
                *(int *)(ptr + offset) = value;


}


        

