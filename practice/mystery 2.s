	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	movl	4(%esp), %ecx
	movl	8(%esp), %edx
	addl	%edx, (%ecx)
	ret
