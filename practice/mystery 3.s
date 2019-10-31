	.text
	.globl mystery
	.type mystery, @function
mystery:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	cmpl $0, %eax
	jge  L1
	subl 12(%ebp), %eax
	jmp  L2
L1:
	addl 12(%ebp), %eax
L2:	
	movl %ebp, %esp
	popl %ebp
	ret
