# example for x86-64 processor using AT&T Style syntax
  .global _start

  .text

  _start:
  	# Write a message to the screen
  	mov $1, %rax  #write syscall
  	mov $1, %rdi  #write to stdout:wq:wq;
  	mov $message, %rsi  #massage to write 
  	mov $13, %rdx  # number of chars 
  	syscall 

  	# Exit the program
  	mov $60, %rax
  	xor %rdi, %rdi
  	syscall

  message:
  	.ascii "Hello, World\n"
