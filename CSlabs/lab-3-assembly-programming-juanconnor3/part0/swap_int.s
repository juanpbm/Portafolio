	.file	"swap_int.c"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp2:
	.cfi_def_cfa_offset 16
.Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp4:
	.cfi_def_cfa_register %rbp
	movl	$0, %eax
	movl	$0, -4(%rbp)
	movl	$5, -8(%rbp)
	movl	$6, -12(%rbp)
	movl	-8(%rbp), %ecx
	movl	%ecx, -16(%rbp)
	movl	-12(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	movl	-16(%rbp), %ecx
	movl	%ecx, -12(%rbp)
	popq	%rbp
	ret
.Ltmp5:
	.size	main, .Ltmp5-main
	.cfi_endproc


	.ident	"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"
	.section	".note.GNU-stack","",@progbits
