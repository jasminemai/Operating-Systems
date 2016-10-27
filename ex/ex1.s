	.file	"ex1.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"-----------------------------------------------"
	.align 8
.LC1:
	.string	"Number of elements in first = %lu\n"
.LC2:
	.string	"first[%d]=%c\n"
.LC3:
	.string	"munsell"
	.align 8
.LC4:
	.string	"first %s, last %s, first initial %c, age %d, male\n"
	.align 8
.LC5:
	.string	"first %s, last %s, first initial %c, age %d, female\n"
.LC6:
	.string	"first %s\n"
	.align 8
.LC7:
	.string	"(p) Memory Location [%p] has value = %d\n"
	.align 8
.LC8:
	.string	"(pp) Memory Location [%p] has value = %d\n"
.LC9:
	.string	"r"
.LC10:
	.string	"test.txt"
.LC11:
	.string	"%s"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movl	%edi, -148(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$98, -80(%rbp)
	movb	$114, -79(%rbp)
	movb	$101, -78(%rbp)
	movb	$110, -77(%rbp)
	movb	$116, -76(%rbp)
	movb	$0, -75(%rbp)
	movl	$.LC0, %edi
	call	puts
	movl	$10, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -140(%rbp)
	jmp	.L2
.L3:
	movl	-140(%rbp), %eax
	cltq
	movzbl	-80(%rbp,%rax), %eax
	movsbl	%al, %edx
	movl	-140(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -140(%rbp)
.L2:
	movl	-140(%rbp), %eax
	cmpl	$9, %eax
	jbe	.L3
	leaq	-80(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	$.LC3, -104(%rbp)
	movl	$44, -96(%rbp)
	movl	$0, -92(%rbp)
	movl	$.LC0, %edi
	call	puts
	movl	-92(%rbp), %eax
	testl	%eax, %eax
	jne	.L4
	movl	-96(%rbp), %esi
	movq	-112(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-104(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L4:
	movl	-96(%rbp), %esi
	movq	-112(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movq	-104(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
.L5:
	movq	-112(%rbp), %rax
	addq	$3, %rax
	movb	$116, (%rax)
	movq	-112(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC0, %edi
	call	puts
	movl	$4, %edi
	call	malloc
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movl	(%rax), %edx
	movq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movq	-136(%rbp), %rax
	movl	$42, (%rax)
	movq	-136(%rbp), %rax
	movl	(%rax), %edx
	movq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movq	-136(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-136(%rbp), %rax
	movl	%edx, (%rax)
	movq	-136(%rbp), %rax
	movl	(%rax), %edx
	movq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-128(%rbp), %rax
	movl	%edx, (%rax)
	movq	-128(%rbp), %rax
	movl	(%rax), %edx
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
	movq	-136(%rbp), %rax
	movl	(%rax), %edx
	movq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC0, %edi
	call	puts
	movl	$.LC9, %esi
	movl	$.LC10, %edi
	call	fopen
	movq	%rax, -120(%rbp)
	cmpq	$0, -120(%rbp)
	je	.L6
	jmp	.L7
.L8:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC11, %edi
	movl	$0, %eax
	call	printf
.L7:
	movq	-120(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movl	$50, %esi
	movq	%rax, %rdi
	call	fgets
	testq	%rax, %rax
	jne	.L8
.L6:
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L10
	call	__stack_chk_fail
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
