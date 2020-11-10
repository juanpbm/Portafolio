	.file	"for.c"
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
	movl	$0, -4(%rbp)
	movl	$0, -12(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$5, -12(%rbp)
	jg	.LBB0_4
# BB#2:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	-8(%rbp), %eax
	addl	$5, %eax
	movl	%eax, -8(%rbp)
# BB#3:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	movl	$0, %eax
	popq	%rbp
	ret
.Ltmp5:
	.size	main, .Ltmp5-main
	.cfi_endproc


	.ident	"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"
	.section	".note.GNU-stack","",@progbits
