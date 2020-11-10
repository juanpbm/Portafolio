	.file	"switch.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movb	$85, -1(%rbp)
	movl	$3, -8(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$76, %eax
	je	.L3
	cmpl	$76, %eax
	jg	.L4
	cmpl	$68, %eax
	je	.L5
	jmp	.L2
.L4:
	cmpl	$82, %eax
	je	.L6
	cmpl	$85, %eax
	je	.L7
	jmp	.L2
.L3:
	subl	$1, -8(%rbp)
	jmp	.L2
.L6:
	addl	$1, -8(%rbp)
	jmp	.L2
.L7:
	addl	$2, -8(%rbp)
	jmp	.L2
.L5:
	subl	$2, -8(%rbp)
	nop
.L2:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)"
	.section	.note.GNU-stack,"",@progbits
