#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>



// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

const int gpio_led1_offset = 0x12C;  // Offset for LED1
const int gpio_led2_offset = 0x130;  // Offset for LED2
const int gpio_led3_offset = 0x134;  // Offset for LED3
const int gpio_led4_offset = 0x138;  // Offset for LED4
const int gpio_led5_offset = 0x13C;  // Offset for LED5
const int gpio_led6_offset = 0x140;  // Offset for LED6
const int gpio_led7_offset = 0x144;  // Offset for LED7
const int gpio_led8_offset = 0x148;  // Offset for LED8

const int gpio_sw1_offset = 0x14C;  // Offset for Switch 1
const int gpio_sw2_offset = 0x150;  // Offset for Switch 2
const int gpio_sw3_offset = 0x154;  // Offset for Switch 3
const int gpio_sw4_offset = 0x158;  // Offset for Switch 4
const int gpio_sw5_offset = 0x15C;  // Offset for Switch 5
const int gpio_sw6_offset = 0x160;  // Offset for Switch 6
const int gpio_sw7_offset = 0x164;  // Offset for Switch 7
const int gpio_sw8_offset = 0x168;  // Offset for Switch 8

const int gpio_pbtnl_offset = 0x16C;  // Offset for left push button
const int gpio_pbtnr_offset = 0x170;  // Offset for right push button
const int gpio_pbtnu_offset = 0x174;  // Offset for up push button
const int gpio_pbtnd_offset = 0x178;  // Offset for down push button
const int gpio_pbtnc_offset = 0x17C;  // Offset for center push button

#ifdef TEST_MODE
#define RegisterWrite RegisterWrite_old
#define RegisterRead RegisterRead_old
#endif

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param ptr       Base address returned by 'mmap'.
 * @param offset    Offset where device is mapped.
 * @param value     Value to be written.
 */
void RegisterWrite(char *ptr, int offset, int value) {
  *(int *)(ptr + offset) = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param ptr       Base address returned by 'mmap'.
 * @param offset    Offset where device is mapped.
 * @return          Value read.
 */
int RegisterRead(char *ptr, int offset) { return *(int *)(ptr + offset); }

#ifdef TEST_MODE
#undef RegisterWrite
#undef RegisterRead
#endif

/**
 * Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param  fd
 *      File descriptor passed by reference, where the result
 *      of function 'open' will be stored.
 *
 * @return
 *      Address to virtual memory which is mapped to physical,
 *      or MAP_FAILED on error.
 */
char *Initialize(int *fd) {
  *fd = open("/dev/mem", O_RDWR);
  return (char *)mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd,
                      gpio_address);
}

/**
 * Close general-purpose I/O.
 *
 * @param ptr   Virtual address where I/O was mapped.
 * @param fd    File descriptor previously returned by 'open'.
 */
void Finalize(char *ptr, int fd) {
  munmap(ptr, gpio_size);
  close(fd);
}

/**
 * Show lower 8 bits of integer value on LEDs
 *
 * @param ptr   Base address of I/O
 * @param value Value to show on LEDs
 */
void SetLedNumber(char *ptr, int value) {
  RegisterWrite(ptr, gpio_led1_offset, value % 2);
  RegisterWrite(ptr, gpio_led2_offset, (value / 2) % 2);
  RegisterWrite(ptr, gpio_led3_offset, (value / 4) % 2);
  RegisterWrite(ptr, gpio_led4_offset, (value / 8) % 2);
  RegisterWrite(ptr, gpio_led5_offset, (value / 16) % 2);
  RegisterWrite(ptr, gpio_led6_offset, (value / 32) % 2);
  RegisterWrite(ptr, gpio_led7_offset, (value / 64) % 2);
  RegisterWrite(ptr, gpio_led8_offset, (value / 128) % 2);
}
	int stateu = 0;
	int stated = 0;
	int statel = 0;
	int stater = 0;
	int statec = 0;
        int counter = 0;


/**
 * PushButtonToLed implements a binary counter.
 *
 * @param ptr Virtual address where I/O was mapped.
 */
void PushButtonToLed(char *ptr) {
  // Write your code here
	//SetLedNumber(ptr, counter); 
	int new_stateu=RegisterRead(ptr,gpio_pbtnu_offset);
	int new_stated=RegisterRead(ptr,gpio_pbtnd_offset);
	int new_statel=RegisterRead(ptr,gpio_pbtnl_offset);
	int new_stater=RegisterRead(ptr,gpio_pbtnr_offset);
	int new_statec=RegisterRead(ptr,gpio_pbtnc_offset);
        int led1 = 0;
 	int led2 = 0;
	int led3 = 0; 
	int led4 = 0; 
	int led5 = 0; 
	int led6 = 0; 
	int led7 = 0; 
	int led8 = 0;
	if ((new_statec!=statec && new_statec == 1) || counter == 0 ){
		
		if(RegisterRead(ptr,gpio_sw1_offset) == 1){
	                RegisterWrite(ptr,gpio_led1_offset,1);
	                led1=1;
		}else{
	                RegisterWrite(ptr,gpio_led1_offset,0);
	
	        }
	        if (RegisterRead(ptr,gpio_sw2_offset)==1){
	                RegisterWrite(ptr,gpio_led2_offset,1);
	     		led2=1;
		}else{
	                RegisterWrite(ptr,gpio_led2_offset,0);

        	}
	        if (RegisterRead(ptr,gpio_sw3_offset)==1){
        	        RegisterWrite(ptr,gpio_led3_offset,1);
	        	led3=1;
		}else{
	                RegisterWrite(ptr,gpio_led3_offset,0);

        	}

	        if (RegisterRead(ptr,gpio_sw4_offset)==1){
        	        RegisterWrite(ptr,gpio_led4_offset,1);
	        	led4=1;
		}else{
	                RegisterWrite(ptr,gpio_led4_offset,0);

        	}
	
		 if (RegisterRead(ptr,gpio_sw5_offset)==1){
        	        RegisterWrite(ptr,gpio_led5_offset,1);
	        	led5=1;
		}else{
        	        RegisterWrite(ptr,gpio_led5_offset,0);

        	}
	        if (RegisterRead(ptr,gpio_sw6_offset)==1){
        	        RegisterWrite(ptr,gpio_led6_offset,1);
	        	led6=1;
		}else{
	                RegisterWrite(ptr,gpio_led6_offset,0);

        	}

	        if (RegisterRead(ptr,gpio_sw7_offset)==1){
	                RegisterWrite(ptr,gpio_led7_offset,1);
		        led7=1;
		}else{
	                RegisterWrite(ptr,gpio_led7_offset,0);

	        }   


        	if (RegisterRead(ptr,gpio_sw8_offset)==1){
	                RegisterWrite(ptr,gpio_led8_offset,1);
		       	led8=1;
		}else{
	                RegisterWrite(ptr,gpio_led8_offset,0);

        	}
            
		counter = (led1*1 + led2*2 + led3*4 + led4*8 + led5*16 + led6*32 + led7*64 + led8*128); 

	}
	statec = new_statec;
	if (new_stateu!=stateu && new_stateu == 1){
		
		counter++;
		SetLedNumber(ptr,counter);

	}
	stateu = new_stateu;
	if(new_stated!=stated && new_stated == 1){

	
		counter--;
		SetLedNumber(ptr,counter);
	}	
	stated = new_stated;
	if(new_statel!=statel && new_statel == 1){


	
		counter=counter<<1;
		SetLedNumber(ptr,counter);
	}	
	statel = new_statel;
	if(new_stater!=stater && new_stater == 1){


		counter=counter>>1;
		SetLedNumber(ptr,counter);

	}
	stater = new_stater;

}
int main() {
  // Initialize
  	int fd;
	 char *ptr = Initialize(&fd);
	int count2=0;
  // Check error
  if (ptr == MAP_FAILED) {
    perror("Mapping I/O memory failed - Did you run with 'sudo'?\n");
    return -1;
  }

  // Update the LED state
  while(true) {
    PushButtonToLed(ptr);
    usleep(5000);
  }

  // Done
  Finalize(ptr, fd);
  return 0;
}
