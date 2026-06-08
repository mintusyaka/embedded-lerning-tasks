	.file	"part1.cpp"
	.text
	.p2align 4
	.globl	_Z18wait_for_flag_safePVjj
	.def	_Z18wait_for_flag_safePVjj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z18wait_for_flag_safePVjj
_Z18wait_for_flag_safePVjj:
.LFB5:
	.seh_endprologue
	movl	(%rcx), %eax
	andl	%edx, %eax
	testl	%eax, %eax
	jne	.L4
	.p2align 3
	.p2align 4
	.p2align 3
.L3:
	addl	$1, %eax
	testl	%edx, (%rcx)
	je	.L3
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%eax, %eax
	ret
	.seh_endproc
	.p2align 4
	.globl	_Z20wait_for_flag_unsafePjj
	.def	_Z20wait_for_flag_unsafePjj;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z20wait_for_flag_unsafePjj
_Z20wait_for_flag_unsafePjj:
.LFB6:
	.seh_endprologue
	testl	%edx, (%rcx)
	jne	.L9
	.p2align 1
	.p2align 4
	.p2align 3
.L10:
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L9:
	xorl	%eax, %eax
	ret
	.seh_endproc
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB7:
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	call	__main
	movl	$0, 44(%rsp)
	movl	44(%rsp), %eax
	andl	$1, %eax
	jne	.L14
	.p2align 4
	.p2align 4
	.p2align 3
.L13:
	addl	$1, %eax
	testb	$1, 44(%rsp)
	je	.L13
.L12:
	addq	$56, %rsp
	ret
.L14:
	xorl	%eax, %eax
	jmp	.L12
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (GNU) 16.1.0"
