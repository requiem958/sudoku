	.file	"clauses.c"
	.text
	.p2align 4,,15
	.globl	new_clause
	.type	new_clause, @function
new_clause:
.LFB5:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movl	$32, %edi
	call	malloc@PLT
	movq	(%rax), %rdx
	movq	%rdx, (%rbx)
	movq	8(%rax), %rdx
	movq	%rdx, 8(%rbx)
	movq	16(%rax), %rdx
	movq	24(%rax), %rax
	movq	%rdx, 16(%rbx)
	movq	%rax, 24(%rbx)
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE5:
	.size	new_clause, .-new_clause
	.p2align 4,,15
	.globl	length
	.type	length, @function
length:
.LFB6:
	.cfi_startproc
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	movq	24(%rdi), %rdi
	addl	$1, %eax
	testq	%rdi, %rdi
	jne	.L5
	rep ret
.L6:
	rep ret
	.cfi_endproc
.LFE6:
	.size	length, .-length
	.p2align 4,,15
	.globl	length2
	.type	length2, @function
length2:
.LFB8:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L13
	movq	24(%rdi), %rdx
	testq	%rdx, %rdx
	je	.L14
	xorl	%eax, %eax
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L15:
	movl	%ecx, %eax
.L12:
	movq	24(%rdx), %rdx
	leal	1(%rax), %ecx
	testq	%rdx, %rdx
	jne	.L15
	addl	$2, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L13:
	xorl	%eax, %eax
	ret
.L14:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE8:
	.size	length2, .-length2
	.p2align 4,,15
	.globl	length3
	.type	length3, @function
length3:
.LFB9:
	.cfi_startproc
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L19
	.p2align 4,,10
	.p2align 3
.L18:
	movq	24(%rdi), %rdi
	addl	$1, %eax
	testq	%rdi, %rdi
	jne	.L18
	rep ret
.L19:
	rep ret
	.cfi_endproc
.LFE9:
	.size	length3, .-length3
	.p2align 4,,15
	.globl	push_var
	.type	push_var, @function
push_var:
.LFB10:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE10:
	.size	push_var, .-push_var
	.p2align 4,,15
	.globl	pop_var
	.type	pop_var, @function
pop_var:
.LFB11:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	pop_var, .-pop_var
	.p2align 4,,15
	.globl	simplify
	.type	simplify, @function
simplify:
.LFB15:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE15:
	.size	simplify, .-simplify
	.p2align 4,,15
	.globl	free_clause
	.type	free_clause, @function
free_clause:
.LFB13:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE13:
	.size	free_clause, .-free_clause
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
