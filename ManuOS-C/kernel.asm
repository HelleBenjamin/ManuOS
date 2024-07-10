	.file	"kernel.c"
	.code16gcc
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -m16 -mtune=generic -march=x86-64 -ffreestanding -fno-pic -fasynchronous-unwind-tables -fstack-clash-protection
	.text
	.globl	printc
	.type	printc, @function
printc:
.LFB0:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$4, %esp	#,
	movl	8(%ebp), %eax	# c, tmp82
	movb	%al, -4(%ebp)	# tmp83, c
# kernel.c:11:     asm("mov %al, 0x95\n\t");
#APP
# 11 "kernel.c" 1
	mov %al, 0x95
	
# 0 "" 2
# kernel.c:12:     asm("call printchr\n\t");
# 12 "kernel.c" 1
	call printchr
	
# 0 "" 2
# kernel.c:13: }
#NO_APP
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE0:
	.size	printc, .-printc
	.globl	prints
	.type	prints, @function
prints:
.LFB1:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
# kernel.c:16:     while (*s) {
	jmp	.L3	#
.L4:
# kernel.c:17:         printc(*s);
	movl	8(%ebp), %eax	# s, tmp85
	movzbl	(%eax), %eax	# *s_4, _1
# kernel.c:17:         printc(*s);
	movsbl	%al, %eax	# _1, _2
	pushl	%eax	# _2
	call	printc	#
	addl	$4, %esp	#,
# kernel.c:18:         s++;
	addl	$1, 8(%ebp)	#, s
.L3:
# kernel.c:16:     while (*s) {
	movl	8(%ebp), %eax	# s, tmp86
	movzbl	(%eax), %eax	# *s_4, _3
	testb	%al, %al	# _3
	jne	.L4	#,
# kernel.c:20: }
	nop	
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE1:
	.size	prints, .-prints
	.globl	getc
	.type	getc, @function
getc:
.LFB2:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$24, %esp	#,
# kernel.c:23:     char c = 0;
	movb	$0, -9(%ebp)	#, c
# kernel.c:24:     getchar();
	call	getchar	#
# kernel.c:25:     asm(
#APP
# 25 "kernel.c" 1
	nop	
# 0 "" 2
#NO_APP
	movb	%al, -9(%ebp)	# c, c
# kernel.c:30: }
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE2:
	.size	getc, .-getc
	.globl	getch
	.type	getch, @function
getch:
.LFB3:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$24, %esp	#,
# kernel.c:33:     char c = 0;
	movb	$0, -9(%ebp)	#, c
.L9:
# kernel.c:35:         c = getc();
	call	getc	#
	movb	%al, -9(%ebp)	# tmp83, c
# kernel.c:36:         if (c != NEWLINE) {
	cmpb	$13, -9(%ebp)	#, c
	jne	.L11	#,
# kernel.c:35:         c = getc();
	jmp	.L9	#
.L11:
# kernel.c:37:             break;
	nop	
# kernel.c:40: }
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE3:
	.size	getch, .-getch
	.globl	m_strcmp
	.type	m_strcmp, @function
m_strcmp:
.LFB4:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	jmp	.L13	#
.L15:
# kernel.c:44:         str1++;
	addl	$1, 8(%ebp)	#, str1
# kernel.c:45:         str2++;
	addl	$1, 12(%ebp)	#, str2
.L13:
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	movl	8(%ebp), %eax	# str1, tmp92
	movzbl	(%eax), %eax	# *str1_9, _1
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	testb	%al, %al	# _1
	je	.L14	#,
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	movl	8(%ebp), %eax	# str1, tmp93
	movzbl	(%eax), %edx	# *str1_9, _2
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	movl	12(%ebp), %eax	# str2, tmp94
	movzbl	(%eax), %eax	# *str2_10, _3
# kernel.c:43:     while (*str1 && (*str1 == *str2)) {
	cmpb	%al, %dl	# _3, _2
	je	.L15	#,
.L14:
# kernel.c:47:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	8(%ebp), %eax	# str1, tmp95
	movzbl	(%eax), %eax	# MEM[(unsigned char *)str1_9], _4
	movzbl	%al, %edx	# _4, _5
# kernel.c:47:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	12(%ebp), %eax	# str2, tmp96
	movzbl	(%eax), %eax	# MEM[(unsigned char *)str2_10], _6
	movzbl	%al, %ecx	# _6, _7
# kernel.c:47:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	%edx, %eax	# _5, _5
	subl	%ecx, %eax	# _7, _5
# kernel.c:48: }
	popl	%ebp	#
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE4:
	.size	m_strcmp, .-m_strcmp
	.section	.rodata
	.align 4
.LC0:
	.string	"Welcome to Wuf++ interpreter, press enter to run the code"
	.align 4
.LC1:
	.string	"Code finished, press enter to run the code again"
	.text
	.globl	wpp_interpreter
	.type	wpp_interpreter, @function
wpp_interpreter:
.LFB5:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	pushl	%ebx	#
	subl	$20, %esp	#,
	.cfi_offset 3, -12
.L18:
# kernel.c:69:     cls();
	call	cls	#
# kernel.c:71:     unsigned int i = 0;
	movl	$0, -12(%ebp)	#, i
# kernel.c:72:     prints("Welcome to Wuf++ interpreter, press enter to run the code");
	subl	$12, %esp	#,
	pushl	$.LC0	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:73:     nl();
	call	nl	#
# kernel.c:75:         i = 0;
	movl	$0, -12(%ebp)	#, i
.L21:
# kernel.c:77:             wpp_buffer[i] = getc();
	movl	-16(%ebp), %edx	# wpp_buffer, tmp95
	movl	-12(%ebp), %eax	# i, tmp96
	leal	(%edx,%eax), %ebx	#, _1
# kernel.c:77:             wpp_buffer[i] = getc();
	call	getc	#
# kernel.c:77:             wpp_buffer[i] = getc();
	movb	%al, (%ebx)	# _2, *_1
# kernel.c:78:             if (wpp_buffer[i] == NEWLINE) {
	movl	-16(%ebp), %edx	# wpp_buffer, tmp97
	movl	-12(%ebp), %eax	# i, tmp98
	addl	%edx, %eax	# tmp97, _3
	movzbl	(%eax), %eax	# *_3, _4
# kernel.c:78:             if (wpp_buffer[i] == NEWLINE) {
	cmpb	$13, %al	#, _4
	jne	.L19	#,
# kernel.c:79:                 wpp_buffer[i] = '\0';
	movl	-16(%ebp), %edx	# wpp_buffer, tmp99
	movl	-12(%ebp), %eax	# i, tmp100
	addl	%edx, %eax	# tmp99, _5
# kernel.c:79:                 wpp_buffer[i] = '\0';
	movb	$0, (%eax)	#, *_5
# kernel.c:80:                 break;
	nop	
# kernel.c:85:         asm("mov %bx, 0x0");
#APP
# 85 "kernel.c" 1
	mov %bx, 0x0
# 0 "" 2
# kernel.c:86:         asm("mov %cx, 0x0");
# 86 "kernel.c" 1
	mov %cx, 0x0
# 0 "" 2
# kernel.c:87:         for (i = 0; wpp_buffer[i] != '\0'; i++) {
#NO_APP
	movl	$0, -12(%ebp)	#, i
# kernel.c:87:         for (i = 0; wpp_buffer[i] != '\0'; i++) {
	jmp	.L22	#
.L19:
# kernel.c:82:             printc(wpp_buffer[i]);
	movl	-16(%ebp), %edx	# wpp_buffer, tmp101
	movl	-12(%ebp), %eax	# i, tmp102
	addl	%edx, %eax	# tmp101, _6
	movzbl	(%eax), %eax	# *_6, _7
# kernel.c:82:             printc(wpp_buffer[i]);
	movsbl	%al, %eax	# _7, _8
	subl	$12, %esp	#,
	pushl	%eax	# _8
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:83:             i++;
	addl	$1, -12(%ebp)	#, i
# kernel.c:77:             wpp_buffer[i] = getc();
	jmp	.L21	#
.L34:
# kernel.c:88:             switch (wpp_buffer[i])
	movl	-16(%ebp), %edx	# wpp_buffer, tmp103
	movl	-12(%ebp), %eax	# i, tmp104
	addl	%edx, %eax	# tmp103, _9
	movzbl	(%eax), %eax	# *_9, _10
	movsbl	%al, %eax	# _10, _11
# kernel.c:88:             switch (wpp_buffer[i])
	subl	$43, %eax	#, tmp105
	cmpl	$50, %eax	#, tmp105
	ja	.L35	#,
	movl	.L25(,%eax,4), %eax	#, tmp106
	jmp	*%eax	# tmp106
	.section	.rodata
	.align 4
	.align 4
.L25:
	.long	.L32
	.long	.L31
	.long	.L30
	.long	.L29
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L28
	.long	.L35
	.long	.L27
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L35
	.long	.L26
	.long	.L35
	.long	.L24
	.text
.L32:
# kernel.c:91:                 asm("inc %bl");
#APP
# 91 "kernel.c" 1
	inc %bl
# 0 "" 2
# kernel.c:92:                 break;
#NO_APP
	jmp	.L33	#
.L30:
# kernel.c:94:                 asm("dec %bl");
#APP
# 94 "kernel.c" 1
	dec %bl
# 0 "" 2
# kernel.c:95:                 break;
#NO_APP
	jmp	.L33	#
.L27:
# kernel.c:97:                 asm("push %bx");
#APP
# 97 "kernel.c" 1
	push %bx
# 0 "" 2
# kernel.c:98:                 break;
#NO_APP
	jmp	.L33	#
.L28:
# kernel.c:100:                 asm("pop %bx");
#APP
# 100 "kernel.c" 1
	pop %bx
# 0 "" 2
# kernel.c:101:                 break;
#NO_APP
	jmp	.L33	#
.L29:
# kernel.c:103:                 asm(
#APP
# 103 "kernel.c" 1
	mov %al, %bl
	call printchr
	
# 0 "" 2
# kernel.c:107:                 break;
#NO_APP
	jmp	.L33	#
.L31:
# kernel.c:109:                 char c = getch();
	call	getch	#
	movb	%al, -21(%ebp)	# tmp107, c
# kernel.c:110:                 asm(
	movzbl	-21(%ebp), %eax	# c, tmp108
#APP
# 110 "kernel.c" 1
	nop	
# 0 "" 2
# kernel.c:115:                 break;
#NO_APP
	jmp	.L33	#
.L26:
# kernel.c:117:                 unsigned int j = 0;
	movl	$0, -20(%ebp)	#, j
# kernel.c:118:                 asm(
#APP
# 118 "kernel.c" 1
	nop	
# 0 "" 2
#NO_APP
	movd	%xmm0, %eax	# j, j
	movl	%eax, -20(%ebp)	# j, j
# kernel.c:123:                 i = i - j;
	movl	-20(%ebp), %eax	# j, tmp110
	subl	%eax, -12(%ebp)	# tmp110, i
# kernel.c:124:                 break;
	jmp	.L33	#
.L24:
# kernel.c:126:                 j = 0;
	movl	$0, -20(%ebp)	#, j
# kernel.c:127:                 asm(
#APP
# 127 "kernel.c" 1
	nop	
# 0 "" 2
#NO_APP
	movd	%xmm1, %eax	# j, j
	movl	%eax, -20(%ebp)	# j, j
# kernel.c:132:                 i = i + j;
	movl	-20(%ebp), %eax	# j, tmp112
	addl	%eax, -12(%ebp)	# tmp112, i
# kernel.c:133:                 break;
	jmp	.L33	#
.L35:
# kernel.c:136:                 break;
	nop	
.L33:
# kernel.c:87:         for (i = 0; wpp_buffer[i] != '\0'; i++) {
	addl	$1, -12(%ebp)	#, i
.L22:
# kernel.c:87:         for (i = 0; wpp_buffer[i] != '\0'; i++) {
	movl	-16(%ebp), %edx	# wpp_buffer, tmp113
	movl	-12(%ebp), %eax	# i, tmp114
	addl	%edx, %eax	# tmp113, _12
	movzbl	(%eax), %eax	# *_12, _13
# kernel.c:87:         for (i = 0; wpp_buffer[i] != '\0'; i++) {
	testb	%al, %al	# _13
	jne	.L34	#,
# kernel.c:139:         nl();
	call	nl	#
# kernel.c:140:         prints("Code finished, press enter to run the code again");
	subl	$12, %esp	#,
	pushl	$.LC1	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:141:         getch();
	call	getch	#
# kernel.c:142:         break;
	nop	
# kernel.c:144:     goto start;
	jmp	.L18	#
	.cfi_endproc
.LFE5:
	.size	wpp_interpreter, .-wpp_interpreter
	.section	.rodata
.LC2:
	.string	"version"
.LC3:
	.string	"ManuOS ManuOS 0.0.1-puppy\n"
.LC4:
	.string	"help"
.LC5:
	.string	"Commands: version, help, wpp"
.LC6:
	.string	"wpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	leal	4(%esp), %ecx	#,
	.cfi_def_cfa 1, 0
	andl	$-16, %esp	#,
	pushl	-4(%ecx)	#
	pushl	%ebp	#
	movl	%esp, %ebp	#,
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%ebx	#
	pushl	%ecx	#
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$16, %esp	#,
# kernel.c:149:     int i = 0;
	movl	$0, -12(%ebp)	#, i
.L43:
# kernel.c:151:         printc('>');
	pushl	$62	#
	call	printc	#
	addl	$4, %esp	#,
# kernel.c:152:         i = 0;
	movl	$0, -12(%ebp)	#, i
.L39:
# kernel.c:154:             prompt[i] = getc();
	movl	-12(%ebp), %edx	# i, i.0_1
	movl	-16(%ebp), %eax	# prompt, tmp97
	leal	(%edx,%eax), %ebx	#, _2
# kernel.c:154:             prompt[i] = getc();
	call	getc	#
# kernel.c:154:             prompt[i] = getc();
	movb	%al, (%ebx)	# _3, *_2
# kernel.c:155:             if (prompt[i] == NEWLINE) {
	movl	-12(%ebp), %edx	# i, i.1_4
	movl	-16(%ebp), %eax	# prompt, tmp98
	addl	%edx, %eax	# i.1_4, _5
	movzbl	(%eax), %eax	# *_5, _6
# kernel.c:155:             if (prompt[i] == NEWLINE) {
	cmpb	$13, %al	#, _6
	jne	.L37	#,
# kernel.c:156:                 prompt[i] = '\0';
	movl	-12(%ebp), %edx	# i, i.2_7
	movl	-16(%ebp), %eax	# prompt, tmp99
	addl	%edx, %eax	# i.2_7, _8
# kernel.c:156:                 prompt[i] = '\0';
	movb	$0, (%eax)	#, *_8
# kernel.c:157:                 break;
	nop	
# kernel.c:163:         if (m_strcmp(prompt, "version") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC2	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:163:         if (m_strcmp(prompt, "version") == 0) {
	testw	%ax, %ax	# _13
	jne	.L40	#,
	jmp	.L44	#
.L37:
# kernel.c:159:             printc(prompt[i]);
	movl	-12(%ebp), %edx	# i, i.3_9
	movl	-16(%ebp), %eax	# prompt, tmp100
	addl	%edx, %eax	# i.3_9, _10
	movzbl	(%eax), %eax	# *_10, _11
# kernel.c:159:             printc(prompt[i]);
	movsbl	%al, %eax	# _11, _12
	subl	$12, %esp	#,
	pushl	%eax	# _12
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:160:             i++;
	addl	$1, -12(%ebp)	#, i
# kernel.c:154:             prompt[i] = getc();
	jmp	.L39	#
.L44:
# kernel.c:164:             prints("ManuOS " VERSION "\n");
	subl	$12, %esp	#,
	pushl	$.LC3	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:165:             nl();
	call	nl	#
	jmp	.L43	#
.L40:
# kernel.c:166:         } else if (m_strcmp(prompt, "help") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC4	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:166:         } else if (m_strcmp(prompt, "help") == 0) {
	testw	%ax, %ax	# _14
	jne	.L42	#,
# kernel.c:167:             prints(HELP_MSG);
	subl	$12, %esp	#,
	pushl	$.LC5	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:168:             nl();
	call	nl	#
	jmp	.L43	#
.L42:
# kernel.c:169:         } else if (m_strcmp(prompt, "wpp") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC6	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:169:         } else if (m_strcmp(prompt, "wpp") == 0) {
	testw	%ax, %ax	# _15
	jne	.L43	#,
# kernel.c:170:             wpp_interpreter();
	call	wpp_interpreter	#
# kernel.c:151:         printc('>');
	jmp	.L43	#
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
