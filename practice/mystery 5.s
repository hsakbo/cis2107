	.text
	.globl mystery
	.type mystery, @function
mystery:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl 	%edi
	movl 	$0, %ecx
	movl	8(%ebp), %edx
	movl 	12(%ebp), %ebx
L1:	
	cmpl	16(%ebp), %ecx
	jge	L2
	movl	(%edx, %ecx, 4), %edi
	movl	%edi, (%ebx, %ecx, 4)
	incl	%ecx
	jmp 	L1
L2:
	popl	%edi
	popl	%ebx
	movl 	%ebp, %esp
	popl	%ebp
	ret
