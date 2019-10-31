	.file	"parser2.c"
	.text
	.globl	line_compressor
	.type	line_compressor, @function
line_compressor:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	addl	$1, -12(%ebp)
.L2:
	subl	$12, %esp
	pushl	8(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	cmpl	$10, -16(%ebp)
	je	.L3
	cmpl	$-1, -16(%ebp)
	je	.L4
	subl	$4, %esp
	pushl	$1
	pushl	$-1
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
.L4:
	movl	-12(%ebp), %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	line_compressor, .-line_compressor
	.globl	space_handle
	.type	space_handle, @function
space_handle:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$4, %esp
	pushl	$1
	pushl	$-3
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	8(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	cmpl	$10, -12(%ebp)
	jne	.L7
	subl	$4, %esp
	pushl	$1
	pushl	$1
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	jmp	.L8
.L9:
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	$32
	call	fputc@PLT
	addl	$16, %esp
.L8:
	subl	$12, %esp
	pushl	8(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	cmpl	$32, -12(%ebp)
	je	.L9
	cmpl	$-1, -12(%ebp)
	je	.L13
	subl	$4, %esp
	pushl	$1
	pushl	$-1
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	jmp	.L13
.L7:
	subl	$4, %esp
	pushl	$1
	pushl	$1
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	nop
.L12:
	subl	$12, %esp
	pushl	8(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	cmpl	$32, -12(%ebp)
	je	.L12
	cmpl	$-1, -12(%ebp)
	je	.L6
	subl	$4, %esp
	pushl	$1
	pushl	$-1
	pushl	8(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	jmp	.L6
.L13:
	nop
.L6:
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	space_handle, .-space_handle
	.globl	quote_handle
	.type	quote_handle, @function
quote_handle:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	$0, -12(%ebp)
	jmp	.L15
.L18:
	cmpb	$10, -13(%ebp)
	jne	.L16
	addl	$1, -12(%ebp)
.L16:
	movsbl	-13(%ebp), %eax
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	%eax
	call	fputc@PLT
	addl	$16, %esp
.L15:
	subl	$12, %esp
	pushl	8(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movb	%al, -13(%ebp)
	cmpb	$34, -13(%ebp)
	je	.L17
	cmpb	$-1, -13(%ebp)
	jne	.L18
.L17:
	cmpb	$-1, -13(%ebp)
	je	.L19
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	$34
	call	fputc@PLT
	addl	$16, %esp
.L19:
	movl	-12(%ebp), %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	quote_handle, .-quote_handle
	.section	.rodata
	.align 4
.LC0:
	.string	"use: parser source destination, args: %d\n"
.LC1:
	.string	"r"
.LC2:
	.string	"source file not found"
.LC3:
	.string	"w"
.LC4:
	.string	"/%c"
	.align 4
.LC5:
	.string	"Error, mismatched quotes\n line %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	subl	$60, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	%ecx, %esi
	movl	$1, -28(%ebp)
	cmpl	$3, (%esi)
	je	.L22
	subl	$8, %esp
	pushl	(%esi)
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L23
.L22:
	movl	4(%esi), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	subl	$8, %esp
	leal	.LC1@GOTOFF(%ebx), %edx
	pushl	%edx
	pushl	%eax
	call	fopen@PLT
	addl	$16, %esp
	movl	%eax, -52(%ebp)
	cmpl	$0, -52(%ebp)
	jne	.L24
	subl	$12, %esp
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L23
.L24:
	movl	4(%esi), %eax
	addl	$8, %eax
	movl	(%eax), %eax
	subl	$8, %esp
	leal	.LC3@GOTOFF(%ebx), %edx
	pushl	%edx
	pushl	%eax
	call	fopen@PLT
	addl	$16, %esp
	movl	%eax, -56(%ebp)
	movl	$0, -32(%ebp)
	movl	$1, -36(%ebp)
	movl	$0, -40(%ebp)
	movl	$2, -44(%ebp)
	jmp	.L25
.L50:
	subl	$12, %esp
	pushl	-52(%ebp)
	call	fgetc@PLT
	addl	$16, %esp
	movb	%al, -57(%ebp)
	cmpl	$7, -28(%ebp)
	ja	.L25
	movl	-28(%ebp), %eax
	sall	$2, %eax
	movl	.L27@GOTOFF(%eax,%ebx), %eax
	addl	%ebx, %eax
	jmp	*%eax
	.section	.rodata
	.align 4
	.align 4
.L27:
	.long	.L25@GOTOFF
	.long	.L33@GOTOFF
	.long	.L32@GOTOFF
	.long	.L31@GOTOFF
	.long	.L30@GOTOFF
	.long	.L29@GOTOFF
	.long	.L28@GOTOFF
	.long	.L26@GOTOFF
	.text
.L33:
	cmpb	$47, -57(%ebp)
	jne	.L34
	movl	$2, -28(%ebp)
	jmp	.L25
.L34:
	cmpb	$34, -57(%ebp)
	jne	.L36
	movl	$6, -28(%ebp)
	jmp	.L25
.L36:
	cmpb	$32, -57(%ebp)
	jne	.L37
	movl	$7, -28(%ebp)
	jmp	.L25
.L37:
	cmpb	$10, -57(%ebp)
	jne	.L38
	movl	$5, -28(%ebp)
	jmp	.L25
.L38:
	movsbl	-57(%ebp), %eax
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	%eax
	call	fputc@PLT
	addl	$16, %esp
	jmp	.L25
.L32:
	cmpb	$42, -57(%ebp)
	jne	.L39
	movl	$3, -28(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	$1, -32(%ebp)
	jmp	.L25
.L39:
	cmpb	$34, -57(%ebp)
	jne	.L41
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$47
	call	fputc@PLT
	addl	$16, %esp
	movl	$6, -28(%ebp)
	jmp	.L25
.L41:
	cmpb	$10, -57(%ebp)
	jne	.L42
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$47
	call	fputc@PLT
	addl	$16, %esp
	movl	$5, -28(%ebp)
	jmp	.L25
.L42:
	cmpb	$32, -57(%ebp)
	jne	.L43
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$47
	call	fputc@PLT
	addl	$16, %esp
	movl	$7, -28(%ebp)
	jmp	.L25
.L43:
	movsbl	-57(%ebp), %eax
	subl	$4, %esp
	pushl	%eax
	leal	.LC4@GOTOFF(%ebx), %eax
	pushl	%eax
	pushl	-56(%ebp)
	call	fprintf@PLT
	addl	$16, %esp
	movl	$1, -28(%ebp)
	jmp	.L25
.L31:
	cmpb	$10, -57(%ebp)
	jne	.L44
	addl	$1, -36(%ebp)
	movl	$0, -44(%ebp)
	jmp	.L45
.L44:
	cmpb	$42, -57(%ebp)
	jne	.L45
	addl	$1, -44(%ebp)
	movl	$4, -28(%ebp)
.L45:
	addl	$1, -44(%ebp)
	jmp	.L25
.L30:
	cmpb	$47, -57(%ebp)
	jne	.L46
	addl	$1, -44(%ebp)
	movl	$0, -48(%ebp)
	jmp	.L47
.L48:
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$32
	call	fputc@PLT
	addl	$16, %esp
	addl	$1, -48(%ebp)
.L47:
	movl	-48(%ebp), %eax
	cmpl	-44(%ebp), %eax
	jl	.L48
	movl	$2, -44(%ebp)
	movl	$0, -32(%ebp)
	movl	$1, -28(%ebp)
	jmp	.L25
.L46:
	addl	$1, -44(%ebp)
	movl	$3, -28(%ebp)
	cmpb	$10, -57(%ebp)
	jne	.L25
	addl	$1, -36(%ebp)
	movl	$0, -44(%ebp)
	jmp	.L25
.L29:
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$10
	call	fputc@PLT
	addl	$16, %esp
	subl	$4, %esp
	pushl	$1
	pushl	$-1
	pushl	-52(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-52(%ebp)
	call	line_compressor
	addl	$16, %esp
	addl	$1, %eax
	addl	%eax, -36(%ebp)
	movl	$1, -28(%ebp)
	jmp	.L25
.L28:
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$34
	call	fputc@PLT
	addl	$16, %esp
	subl	$4, %esp
	pushl	$1
	pushl	$-1
	pushl	-52(%ebp)
	call	fseek@PLT
	addl	$16, %esp
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	-52(%ebp)
	call	quote_handle
	addl	$16, %esp
	addl	%eax, -36(%ebp)
	movl	$1, -28(%ebp)
	jmp	.L25
.L26:
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$32
	call	fputc@PLT
	addl	$16, %esp
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	-52(%ebp)
	call	space_handle
	addl	$16, %esp
	movl	$1, -28(%ebp)
	nop
.L25:
	subl	$12, %esp
	pushl	-52(%ebp)
	call	feof@PLT
	addl	$16, %esp
	testl	%eax, %eax
	je	.L50
	subl	$12, %esp
	pushl	-52(%ebp)
	call	fclose@PLT
	addl	$16, %esp
	subl	$8, %esp
	pushl	-56(%ebp)
	pushl	$10
	call	fputc@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-56(%ebp)
	call	fclose@PLT
	addl	$16, %esp
	cmpl	$1, -32(%ebp)
	jne	.L51
	subl	$8, %esp
	pushl	-40(%ebp)
	leal	.LC5@GOTOFF(%ebx), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
.L51:
	movl	$0, %eax
.L23:
	leal	-12(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB4:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE4:
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
