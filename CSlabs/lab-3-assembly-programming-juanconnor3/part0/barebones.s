# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans: The entry to main function. First we store the 
	pushq %rbp			# previous rpb (bottom address of the stack) to the top stack	
	movq  %rsp, %rbp		# then we change rbp to the current top of the stack. This is to 
					# keep track of local and global variables.  

					# (2) What is going on here
					# Ans: setting up the parameters for syscall
	movq $1, %rax			# rax set to 1 means that the syscall will write 
	movq $1, %rdi			# rdi set to 1 means write to stdout 
	leaq .hello.str,%rsi		# rsi contains the value that will be printed 


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: Is the command to request a service from the OS
	syscall				# Which syscall is being run?
					# Ans: Write 

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: callq printf if stdio.h was included
					# in the code 

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans: The command is exit. It is used to terminate the process	
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans:	13 is the length of the string "Hello World\n" where \n 
					# counts as 1
