#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>

class ZedBoard {
private:
	unsigned gpio_address;
	unsigned gpio_size;
	char *ptr;
	int fd;
	int gpio_led1_offset;  // Offset for LED1
	int gpio_led2_offset;  // Offset for LED2
	int gpio_led3_offset;  // Offset for LED3
	int gpio_led4_offset;  // Offset for LED4
	int gpio_led5_offset;  // Offset for LED5
	int gpio_led6_offset;  // Offset for LED6
	int gpio_led7_offset;  // Offset for LED7
	int gpio_led8_offset;  // Offset for LED8
public:   
	ZedBoard(){        
	
		gpio_address = 0x400d0000;
		gpio_size = 0xff;
		gpio_led1_offset = 0x12C;  // Offset for LED1
		gpio_led2_offset = 0x130;  // Offset for LED2
		gpio_led3_offset = 0x134;  // Offset for LED3
		gpio_led4_offset = 0x138;  // Offset for LED4
		gpio_led5_offset = 0x13C;  // Offset for LED5
		gpio_led6_offset = 0x140;  // Offset for LED6
		gpio_led7_offset = 0x144;  // Offset for LED7
		gpio_led8_offset = 0x148;  // Offset for LED8
		fd = open("/dev/mem", O_RDWR);
		ptr =  (char *)mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
	

        }  
	~ZedBoard() {        
		 munmap(ptr, gpio_size);
		 close(fd);
 
        }
	void RegisterWrite(char *ptr, int offset, int value);

 	int RegisterRead(char *ptr, int offset);

	void SetLedByValue(int value);





};
