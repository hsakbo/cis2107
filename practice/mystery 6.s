	.text
	.type mystery, @function
	.type mystery2, @function
	.globl mystery
mystery:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %edx
	movl $0, %ecx
L1:
	cmpl 12(%ebp), %ecx
	jge L2
	pushl (%edx, %ecx, 4)
	call mystery2
	addl $4, %esp
	movl %eax, (%edx, %ecx, 4)
	incl %ecx
	jmp L1
L2:	
	movl %ebp, %esp
	popl %ebp
	ret


mystery2:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	addl %eax, %eax
	movl %ebp, %esp
	popl %ebp
	ret
	
	
