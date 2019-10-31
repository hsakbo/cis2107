	.text
	.globl mystery
	.type mystery, @function
mystery:
	pushl %ebp
	movl  %esp, %ebp
	movl  $0, %eax
	movl  $0, %ecx
	movl  8(%ebp), %edx
L1:
	cmpl  12(%ebp), %ecx
	jge   L2
	addl  (%edx, %ecx, 4), %eax
	incl  %ecx
	jmp   L1
L2:	
	movl  %ebp, %esp
	popl  %ebp
	ret
