	.file	"input.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$-10, -20(%rbp)
	movl	$10, -16(%rbp)
	movl	$-5, -12(%rbp)
	movl	-16(%rbp), %eax
	subl	-20(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	addl	%edx, %ecx
	movl	-20(%rbp), %edx
	addl	%ecx, %edx
	subl	%edx, %eax
	leal	-33(%rax), %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-12(%rbp), %eax
	negl	%eax
	movl	%eax, %esi
	movl	-20(%rbp), %eax
	cltd
	idivl	%esi
	imull	-16(%rbp), %eax
	movl	%eax, %ecx
	movl	-20(%rbp), %eax
	imull	-16(%rbp), %eax
	cltd
	idivl	-12(%rbp)
	imull	-20(%rbp), %eax
	addl	%eax, %ecx
	movl	-20(%rbp), %eax
	subl	-16(%rbp), %eax
	movl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	subl	-8(%rbp), %eax
	movl	-20(%rbp), %edx
	negl	%edx
	imull	%edx, %eax
	addl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
