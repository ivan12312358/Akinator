	.file	"131.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%p\t0x%0.2x\n"
	.text
	.globl	_Z10show_bytesPhi
	.type	_Z10show_bytesPhi, @function
_Z10show_bytesPhi:
.LFB13:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movl	%esi, %ebp
	movl	$0, %ebx
	jmp	.L3
.L5:
	movslq	%ebx, %rsi
	addq	%r12, %rsi
	movzbl	(%rsi), %edx
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, %ebx
.L3:
	cmpl	%ebp, %ebx
	jl	.L5
	movl	$10, %edi
	call	putchar@PLT
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	_Z10show_bytesPhi, .-_Z10show_bytesPhi
	.section	.rodata.str1.1
.LC1:
	.string	"int a = %d;\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movl	$15, 4(%rsp)
	movl	$15, %esi
	leaq	.LC1(%rip), %rdi
	call	printf@PLT
	leaq	4(%rsp), %rdi
	movl	$4, %esi
	call	_Z10show_bytesPhi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L9
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
