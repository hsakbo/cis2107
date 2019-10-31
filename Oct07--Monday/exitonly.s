
	.section .data
	.section .text
	.globl _start

_start:
	movl $20, %ebx /*this is the linux kernel command */
			/*number (sys call) for exiting
	/*a program*/
	addl $30, %ebx
	movl $1, %eax	/*this is the status number we will */
			/*Change this around and it will return different things to echo $? */
	int $0x80	/*this wakes up the kernel to run */
	/* the exit command */

	/*movl %ebx, %eax
	mov{b,w,l,q}
note:	 when accessing register use %... */
	
