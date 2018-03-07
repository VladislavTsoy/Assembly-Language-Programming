.globl nCr
	.type	nCr, @function
nCr:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%rbx
	subq	$24, %rsp
	movl	%edi, -28(%rbp)
	movl	%esi, -32(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	factorial
	movl	%eax, -12(%rbp)
	movl	-32(%rbp), %eax
	movl	-28(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	factorial
	movl	%eax, %ebx
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	factorial
	imull	%ebx, %eax
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	cltd
	idivl	-20(%rbp)
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	ret

.globl Factorial
	.type	Factorial, @function
factorial:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -20(%rbp)
	movl	$1, -8(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L12
.L13:
	movl	-8(%rbp), %eax
	imull	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jle	.L13
	movl	-8(%rbp), %eax
	popq	%rbp
	ret
	

