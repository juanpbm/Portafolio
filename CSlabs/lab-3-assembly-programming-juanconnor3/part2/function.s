#function to add or subtract two long numbers 
#please compile using clang function.s -nostartfiles -g -o function
#to link the C libraries used 

.global _start

.equ READ, 0
.equ WRITE, 1
.equ EXIT, 60

.bss 
	OPERATION: .skip 8 
	NUM1: .skip 8
	NUM2: .skip 8
	SOL: .skip 8

.text

#function to add 2 numbers 
_add:

	movq NUM1, %r9
	movq NUM2, %r10
	addq %r9, %r10
	movq %r10, SOL
	ret
#function to subtract 2 numbers 
_subtract:

	movq NUM1, %r9
	movq NUM2, %r10
	subq %r10, %r9
	movq %r9, SOL
	ret
#function to print the results 
_print:

	movq SOL, %rsi
	movabsq $.L.str, %rdi
	movb $0, %al
	callq printf
	movl $0, %ecx
	ret
.L.str:
        .asciz  "%lld\n"
      
#main 
_start:

	movq %rsp, %rbp
#write and get user input
	movq $WRITE, %rax
	movq $1, %rdi
	leaq MSG1, %rsi
	movq $39, %rdx
	syscall

	movq $READ, %rax
	movq $0, %rdi
	movq $OPERATION, %rsi
	movq $8, %rdx
	syscall

	movq $READ, %rax
	movq $0, %rdi
	movq $NUM1, %rsi
	movq $8, %rdx
	syscall

	movq $READ, %rax
	movq $0, %rdi
	movq $NUM2, %rsi
	movq $8, %rdx
	syscall
#convert string to long
	leaq [OPERATION], %rax
	movq %rax, %rdi
	callq atoi
	movq %rax, OPERATION

	leaq [NUM1], %rax
	movq %rax, %rdi
	callq atoi
	movq %rax, NUM1 

	leaq [NUM2], %rax
	movq %rax, %rdi
	callq atoi
	movq %rax, NUM2
#call add or subtract depending on user input 	
	cmpq $1, OPERATION
	je L1
	jne L2


	pop %rbp

MSG1:
	.ascii "Select an operation\n1- add\n2- subtract\n"
#call add
L1:
	call _add
 	call _print 
	movq $EXIT, %rax
	movq $0, %rdi
	syscall
#call subtract :
L2:
	call _subtract
	call _print
	movq $EXIT, %rax
	movq $0, %rdi
	syscall


