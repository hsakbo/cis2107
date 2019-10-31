	.file	"mystery.c"
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	movl	8(%esp), %eax
	addl	4(%esp), %eax
	subl	12(%esp), %eax
	ret
