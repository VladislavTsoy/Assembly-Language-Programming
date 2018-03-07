#include <stdlib.h>
#include <stdio.h>

/*
* There are 3 functions in mystery.c
*		-add
*		-dothething
*		-main
*
* The program computes the fibinacci sequence
* The user enters a value - outputs the corresponding number in the fibinacci sequence
*/
int num[200];
/*
* The following is the add function:
*	add:
*		pushq	%rbp					#save rbp on the stack
*		movq	%rsp, %rbp				#store the value of rsp to rbp
*		movq	%rdi, -8(%rbp)			#stores int a in rbp[-2]
*		movq	%rsi, -16(%rbp)			#stores int b in rbp[-4]
*		movq	-16(%rbp), %rax			#stores int b in rax
*		movq	-8(%rbp), %rdx			#stores int a in rdx
*		addq	%rdx, %rax				#adds a + b in rax register
*		popq	%rbp					#reset frame pointer
*		ret 							#returns rax
*/

int add(int a, int b){
	return b + a;
}

/*
* The following the is dothething function:
*   dothething:
*		pushq	%rbp					#save rbp on the stack
*		movq	%rsp, %rbp				#store the value of rsp to rbp
*		pushq	%rbx					#stores temporary value;
*		subq	$40, %rsp				#allocate 40-byte stack frame
*		movq	%rdi, -40(%rbp)			#stores x in rbp[-5]
*		movq	-40(%rbp), %rax			#stores value of x in rax
*		movq	num(,%rax,8), %rax		#num[value of rax] 
*		cmpq	$-1, %rax				#compares num[rax] == -1
*		je	.L4							#if num[x] == -1, jump to .L4
*		movq	-40(%rbp), %rax			
*		movq	num(,%rax,8), %rax		#
*		jmp	.L5							#jump to .L5
*	.L4:
*		movq	$-1, -24(%rbp)			#stores -1 in rbp[-3]			
*		cmpq	$0, -40(%rbp)			#if x == 0
*		jne	.L6							#jump to .L6 if x != 0
*		movq	$0, -24(%rbp)			#rbp[-3] = 0
*		jmp	.L7							#jump to .L7
*	.L6:
*		cmpq	$1, -40(%rbp)   		#compare x == 1
*		jne	.L8							#if not equal, jump to .L8
*		movq	$1, -24(%rbp)			#rbp[-3] = 1
*		jmp	.L7							#if equal jump to .L7
*	.L8:								#recursion occurs in this jump
*		movq	-40(%rbp), %rax			#rax = x
*		subq	$2, %rax				#rax - 2		
*		movq	%rax, %rdi				#rax - 2 = first argument
*		call	dothething				#calls dothething
*		movq	%rax, %rbx				#stored in rbx
*		movq	-40(%rbp), %rax
*		subq	$1, %rax				#rax - 1
*		movq	%rax, %rdi				#rax - 1 = first argument
*		call	dothething				#call dothething
*		movq	%rbx, %rsi 				#rsi = rbx
*		movq	%rax, %rdi 				#rdi = result 
*		call	add 					#add dothething(x-1) + dothething(X+2)
*		movq	%rax, -24(%rbp)
*	.L7:
*		movq	-40(%rbp), %rax			#rax = x
*		movq	num(,%rax,8), %rax		#compare rax[x]
*		cmpq	$-1, %rax				#to -1
*		jne	.L9							if not equal jump to .L9
*		movq	-40(%rbp), %rax
*		movq	-24(%rbp), %rdx
*		movq	%rdx, num(,%rax,8)		#num[x] = value;
*	.L9:
*		movq	-40(%rbp), %rax
*		movq	num(,%rax,8), %rax
*	.L5:
*		addq	$40, %rsp			
*		popq	%rbx
*		popq	%rbp
*		ret 							#returns num[x]
*/

int dothething(int x){

	if(num[x] == -1) {
		if(x == 0) {
			num[x] = 0;

		} else if(x == 1) {
			num[x] = 1;

		} else {
			num[x] = dothething(x-1) + dothething(x-2);
		}
	}

	return num[x];

}
/*
* main:
*		pushq	%rbp				#save rbp on the stacj
*		movq	%rsp, %rbp			#rbp = rsp
*		subq	$32, %rsp			#allocate 32 bytes in rsp
*		movl	%edi, -20(%rbp)		#edi is argument 1
*		movq	%rsi, -32(%rbp)		#rbp[-4] = argument 2
*		movq	-32(%rbp), %rax		#rax = argument 2
*		addq	$8, %rax			#rax = argv[1]
*		movq	(%rax), %rax		#
*		movq	%rax, %rdi			#rdi = rax
*		call	atoi				#call atoi function on argv[1]
*		movl	%eax, -8(%rbp)		#rbp[-2] = atoi(argv[1])	
*		movl	$0, -4(%rbp)		#rbp[-1] = 0;
*		jmp	.L11
*	.L12:
*		movl	-4(%rbp), %eax		#
*		cltq						#convert long to quad
*		movq	$-1, num(,%rax,8)	
*		addl	$1, -4(%rbp)
*	.L11:
*		cmpl	$199, -4(%rbp) 		#if (0 <= 199)
*		jle	.L12					# if true, jump to .L12
*		movl	-8(%rbp), %eax		#eax = value
*		cltq						#converts to quad
*		movq	%rax, %rdi 			#rdi = rax
*		call	dothething			#calls dothething
*		movq	%rax, %rsi 			#rsi = rax
*		movl	$.LC0, %edi 		#moves string into arg1
*		movl	$0, %eax 			#eax = 0;
*		call	printf
*		movl	$0, %eax
*		leave
*		ret
*/

int main(int argc,char **argv) {
	int value = atoi(argv[1]);
	int i = 0;

	while (i <= 199) {
		num[i] = -1;
		i ++;
	}
	printf("Value:  %d\n", dothething(value));
	return 0;

}

/*
* The following is the add function:
*	add:
*		pushq	%rbp					#save rbp on the stack
*		movq	%rsp, %rbp				#store the value of rsp to rbp
*		movq	%rdi, -8(%rbp)			#stores int a in rbp[-2]
*		movq	%rsi, -16(%rbp)			#stores int b in rbp[-4]
*		movq	-16(%rbp), %rax			#stores int b in rax
*		movq	-8(%rbp), %rdx			#stores int a in rdx
*		addq	%rdx, %rax				#adds a + b in rax register
*		popq	%rbp					#reset frame pointer
*		ret 							#returns rax
*/

