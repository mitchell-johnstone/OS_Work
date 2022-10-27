	.file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"USER"
.LC1:
	.string	"Hello %s:%s:%s:%s:z%s\n"
	.align 8
.LC2:
	.string	"The size of the UTS structure is %lu.\n"
	.align 8
.LC3:
	.string	"User information not returned by the operating system."
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movl	%edi, -420(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-400(%rbp), %rax
	movq	%rax, %rdi
	call	uname@PLT
	leaq	.LC0(%rip), %rdi
	call	getenv@PLT
	movq	%rax, -408(%rbp)
	leaq	-400(%rbp), %rax
	leaq	260(%rax), %rdi
	leaq	-400(%rbp), %rax
	leaq	195(%rax), %rsi
	leaq	-400(%rbp), %rax
	leaq	130(%rax), %rcx
	leaq	-400(%rbp), %rax
	leaq	65(%rax), %rdx
	leaq	-400(%rbp), %rax
	movq	%rdi, %r9
	movq	%rsi, %r8
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$390, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpq	$0, -408(%rbp)
	je	.L2
	movq	-408(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L3
.L2:
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L3:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
