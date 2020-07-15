	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"|/-\\"
.LC1:
	.string	"[%-100s][%d%%][%c]\r"
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
	addq	$-128, %rsp
	movl	$0, -4(%rbp)
	leaq	-128(%rbp), %rax
	movl	$102, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	$.LC0, -16(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltd
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movl	-4(%rbp), %edx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	cltq
	movb	$35, -128(%rbp,%rax)
	movl	$10000, %edi
	call	usleep
.L2:
	cmpl	$100, -4(%rbp)
	jle	.L3
	movl	$10, %edi
	call	putchar
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
