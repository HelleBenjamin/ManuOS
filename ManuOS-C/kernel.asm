	.file	"kernel.c"
	.code16gcc
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -m16 -mtune=generic -march=x86-64 -ffreestanding -fno-pic -fasynchronous-unwind-tables -fstack-clash-protection
	.text
	.globl	numToAscii
	.type	numToAscii, @function
numToAscii:
.LFB0:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
# kernel.c:14:     return '0' + num;
	movl	8(%ebp), %eax	# num, tmp86
	addl	$48, %eax	#, _2
# kernel.c:15: }
	popl	%ebp	#
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE0:
	.size	numToAscii, .-numToAscii
	.globl	asciiToNum
	.type	asciiToNum, @function
asciiToNum:
.LFB1:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$4, %esp	#,
	movl	8(%ebp), %eax	# c, tmp86
	movb	%al, -4(%ebp)	# tmp87, c
# kernel.c:17:     return c - 48;
	movsbw	-4(%ebp), %ax	# c, _1
	subl	$48, %eax	#, _2
# kernel.c:18: }
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE1:
	.size	asciiToNum, .-asciiToNum
	.globl	printc
	.type	printc, @function
printc:
.LFB2:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$4, %esp	#,
	movl	8(%ebp), %eax	# c, tmp82
	movb	%al, -4(%ebp)	# tmp83, c
# kernel.c:20:     asm(
	movzbl	-4(%ebp), %eax	# c, tmp84
#APP
# 20 "kernel.c" 1
	nop
		
# 0 "" 2
# kernel.c:25:     asm("call printchr\n\t");
# 25 "kernel.c" 1
	call printchr
	
# 0 "" 2
# kernel.c:26: }
#NO_APP
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE2:
	.size	printc, .-printc
	.globl	prints
	.type	prints, @function
prints:
.LFB3:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
# kernel.c:29:     while (*s) {
	jmp	.L7	#
.L8:
# kernel.c:30:         printc(*s);
	movl	8(%ebp), %eax	# s, tmp85
	movzbl	(%eax), %eax	# *s_4, _1
# kernel.c:30:         printc(*s);
	movsbl	%al, %eax	# _1, _2
	pushl	%eax	# _2
	call	printc	#
	addl	$4, %esp	#,
# kernel.c:31:         s++;
	addl	$1, 8(%ebp)	#, s
.L7:
# kernel.c:29:     while (*s) {
	movl	8(%ebp), %eax	# s, tmp86
	movzbl	(%eax), %eax	# *s_4, _3
	testb	%al, %al	# _3
	jne	.L8	#,
# kernel.c:33: }
	nop	
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE3:
	.size	prints, .-prints
	.globl	printi
	.type	printi, @function
printi:
.LFB4:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	pushl	%ebx	#
	subl	$16, %esp	#,
	.cfi_offset 3, -12
# kernel.c:37:     int j = 0;
	movl	$0, -8(%ebp)	#, j
# kernel.c:38:     if (i < 0) {
	cmpl	$0, 8(%ebp)	#, i
	jns	.L11	#,
# kernel.c:39:         printc('-');
	pushl	$45	#
	call	printc	#
	addl	$4, %esp	#,
# kernel.c:40:         i *= -1;
	negl	8(%ebp)	# i
# kernel.c:42:     while (i > 0) {
	jmp	.L11	#
.L12:
# kernel.c:43:         buf[j++] = i % 10 + '0';
	movl	8(%ebp), %ecx	# i, tmp89
	movl	$1717986919, %edx	#, tmp91
	movl	%ecx, %eax	# tmp89, tmp106
	imull	%edx	# tmp91
	movl	%edx, %eax	# tmp90, tmp90
	sarl	$2, %eax	#, tmp90
	movl	%ecx, %ebx	# tmp89, tmp93
	sarl	$31, %ebx	#, tmp93
	subl	%ebx, %eax	# tmp93, tmp92
	movl	%eax, %edx	# tmp92, _1
	movl	%edx, %eax	# _1, tmp94
	sall	$2, %eax	#, tmp94
	addl	%edx, %eax	# _1, tmp94
	addl	%eax, %eax	# tmp95
	subl	%eax, %ecx	# tmp94, tmp89
	movl	%ecx, %edx	# tmp89, _1
# kernel.c:43:         buf[j++] = i % 10 + '0';
	movl	%edx, %eax	# _1, _2
	leal	48(%eax), %ecx	#, _3
# kernel.c:43:         buf[j++] = i % 10 + '0';
	movl	-8(%ebp), %eax	# j, j.0_4
	leal	1(%eax), %edx	#, tmp96
	movl	%edx, -8(%ebp)	# tmp96, j
# kernel.c:43:         buf[j++] = i % 10 + '0';
	movl	%ecx, %edx	# _3, _5
# kernel.c:43:         buf[j++] = i % 10 + '0';
	movb	%dl, -18(%ebp,%eax)	# _5, buf[j.0_4]
# kernel.c:44:         i /= 10;
	movl	8(%ebp), %ecx	# i, tmp98
	movl	$1717986919, %edx	#, tmp100
	movl	%ecx, %eax	# tmp98, tmp107
	imull	%edx	# tmp100
	movl	%edx, %eax	# tmp99, tmp99
	sarl	$2, %eax	#, tmp99
	sarl	$31, %ecx	#, tmp98
	movl	%ecx, %edx	# tmp98, tmp102
	subl	%edx, %eax	# tmp102, tmp97
	movl	%eax, 8(%ebp)	# tmp97, i
.L11:
# kernel.c:42:     while (i > 0) {
	cmpl	$0, 8(%ebp)	#, i
	jg	.L12	#,
# kernel.c:46:     while (j > 0) {
	jmp	.L13	#
.L14:
# kernel.c:47:         printc(buf[--j]);
	subl	$1, -8(%ebp)	#, j
# kernel.c:47:         printc(buf[--j]);
	leal	-18(%ebp), %edx	#, tmp103
	movl	-8(%ebp), %eax	# j, tmp105
	addl	%edx, %eax	# tmp103, tmp104
	movzbl	(%eax), %eax	# buf[j_21], _6
# kernel.c:47:         printc(buf[--j]);
	movsbl	%al, %eax	# _6, _7
	pushl	%eax	# _7
	call	printc	#
	addl	$4, %esp	#,
.L13:
# kernel.c:46:     while (j > 0) {
	cmpl	$0, -8(%ebp)	#, j
	jg	.L14	#,
# kernel.c:49: }
	nop	
	nop	
	movl	-4(%ebp), %ebx	#,
	leave	
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE4:
	.size	printi, .-printi
	.globl	getc
	.type	getc, @function
getc:
.LFB5:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$24, %esp	#,
# kernel.c:52:     char c = 0;
	movb	$0, -9(%ebp)	#, c
# kernel.c:53:     getchar();
	call	getchar	#
# kernel.c:54:     asm(
#APP
# 54 "kernel.c" 1
	nop	
# 0 "" 2
#NO_APP
	movb	%al, -9(%ebp)	# c, c
# kernel.c:59: }
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE5:
	.size	getc, .-getc
	.globl	getch
	.type	getch, @function
getch:
.LFB6:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$24, %esp	#,
# kernel.c:62:     char c = 0;
	movb	$0, -9(%ebp)	#, c
.L19:
# kernel.c:64:         c = getc();
	call	getc	#
	movb	%al, -9(%ebp)	# tmp83, c
# kernel.c:65:         if (c != 0) {
	cmpb	$0, -9(%ebp)	#, c
	jne	.L21	#,
# kernel.c:64:         c = getc();
	jmp	.L19	#
.L21:
# kernel.c:66:             break;
	nop	
# kernel.c:69: }
	nop	
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE6:
	.size	getch, .-getch
	.globl	m_strcmp
	.type	m_strcmp, @function
m_strcmp:
.LFB7:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	jmp	.L23	#
.L25:
# kernel.c:73:         str1++;
	addl	$1, 8(%ebp)	#, str1
# kernel.c:74:         str2++;
	addl	$1, 12(%ebp)	#, str2
.L23:
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	movl	8(%ebp), %eax	# str1, tmp92
	movzbl	(%eax), %eax	# *str1_9, _1
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	testb	%al, %al	# _1
	je	.L24	#,
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	movl	8(%ebp), %eax	# str1, tmp93
	movzbl	(%eax), %edx	# *str1_9, _2
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	movl	12(%ebp), %eax	# str2, tmp94
	movzbl	(%eax), %eax	# *str2_10, _3
# kernel.c:72:     while (*str1 && (*str1 == *str2)) {
	cmpb	%al, %dl	# _3, _2
	je	.L25	#,
.L24:
# kernel.c:76:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	8(%ebp), %eax	# str1, tmp95
	movzbl	(%eax), %eax	# MEM[(unsigned char *)str1_9], _4
	movzbl	%al, %edx	# _4, _5
# kernel.c:76:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	12(%ebp), %eax	# str2, tmp96
	movzbl	(%eax), %eax	# MEM[(unsigned char *)str2_10], _6
	movzbl	%al, %ecx	# _6, _7
# kernel.c:76:     return *(unsigned char *)str1 - *(unsigned char *)str2;
	movl	%edx, %eax	# _5, _5
	subl	%ecx, %eax	# _7, _5
# kernel.c:77: }
	popl	%ebp	#
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE7:
	.size	m_strcmp, .-m_strcmp
	.globl	random
	.type	random, @function
random:
.LFB8:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$16, %esp	#,
# kernel.c:84:     asm("mov %ax, %ax\n\t");
#APP
# 84 "kernel.c" 1
	mov %ax, %ax
	
# 0 "" 2
# kernel.c:85:     asm(
# 85 "kernel.c" 1
	nop
		
# 0 "" 2
#NO_APP
	movl	%eax, -4(%ebp)	# seed, seed
# kernel.c:91:     return (seed % (max - min + 1)) + min;
	movl	12(%ebp), %eax	# max, tmp89
	subl	8(%ebp), %eax	# min, _1
# kernel.c:91:     return (seed % (max - min + 1)) + min;
	leal	1(%eax), %ecx	#, _2
# kernel.c:91:     return (seed % (max - min + 1)) + min;
	movl	-4(%ebp), %eax	# seed, tmp90
	cltd
	idivl	%ecx	# _2
# kernel.c:91:     return (seed % (max - min + 1)) + min;
	movl	8(%ebp), %eax	# min, tmp93
	addl	%edx, %eax	# _3, _4
# kernel.c:92: }
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE8:
	.size	random, .-random
	.globl	diceroll
	.type	diceroll, @function
diceroll:
.LFB9:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	subl	$16, %esp	#,
.L32:
# kernel.c:96:         int dice = random(1, 6);
	pushl	$6	#
	pushl	$1	#
	call	random	#
	addl	$8, %esp	#,
# kernel.c:96:         int dice = random(1, 6);
	movl	%eax, -4(%ebp)	# _1, dice
# kernel.c:97:         if (dice < 6 && dice > 1) {
	cmpl	$5, -4(%ebp)	#, dice
	jg	.L35	#,
# kernel.c:97:         if (dice < 6 && dice > 1) {
	cmpl	$1, -4(%ebp)	#, dice
	jle	.L35	#,
# kernel.c:98:             return dice;
	movl	-4(%ebp), %eax	# dice, _6
	jmp	.L34	#
.L35:
# kernel.c:100:             continue;
	nop	
# kernel.c:95:     while (1) {
	jmp	.L32	#
.L34:
# kernel.c:104: }
	leave	
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE9:
	.size	diceroll, .-diceroll
	.section	.rodata
.LC0:
	.string	"YATZY"
.LC1:
	.string	"Press enter to roll"
.LC2:
	.string	"Rolling..."
.LC3:
	.string	"Rolls remaining: "
.LC4:
	.string	"Your dices are: "
	.align 4
.LC5:
	.string	"                 ^   ^   ^   ^   ^"
	.align 4
.LC6:
	.string	"Dice numbers:    1   2   3   4   5"
.LC7:
	.string	"What do you want to do?"
.LC8:
	.string	"1 - Reroll"
.LC9:
	.string	"2 - Score"
.LC10:
	.string	"Which dices to reroll?"
	.text
	.globl	yatzy
	.type	yatzy, @function
yatzy:
.LFB10:
	.cfi_startproc
	pushl	%ebp	#
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp	#,
	.cfi_def_cfa_register 5
	pushl	%edi	#
	subl	$132, %esp	#,
	.cfi_offset 7, -12
# kernel.c:107:     cls();
	call	cls	#
# kernel.c:108:     prints("YATZY");
	subl	$12, %esp	#,
	pushl	$.LC0	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:109:     nl();
	call	nl	#
# kernel.c:110:     int scoreboard[16] = {0}; 
	leal	-96(%ebp), %edx	#, tmp95
	movl	$0, %eax	#, tmp96
	movl	$16, %ecx	#, tmp97
	movl	%edx, %edi	# tmp95, tmp95
	rep stosl
# kernel.c:129:     int dices[5] = {0};
	movl	$0, -116(%ebp)	#, dices
	movl	$0, -112(%ebp)	#, dices
	movl	$0, -108(%ebp)	#, dices
	movl	$0, -104(%ebp)	#, dices
	movl	$0, -100(%ebp)	#, dices
# kernel.c:130:     int rollsRemaining = 3;
	movl	$3, -12(%ebp)	#, rollsRemaining
.L59:
# kernel.c:132:         prints("Press enter to roll");
	subl	$12, %esp	#,
	pushl	$.LC1	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:133:         getch();
	call	getch	#
# kernel.c:134:         prints("Rolling...");
	subl	$12, %esp	#,
	pushl	$.LC2	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:135:         nl();
	call	nl	#
# kernel.c:136:         for (int i = 0; i < 5; i++) {
	movl	$0, -16(%ebp)	#, i
# kernel.c:136:         for (int i = 0; i < 5; i++) {
	jmp	.L37	#
.L38:
# kernel.c:137:             dices[i] = diceroll();
	call	diceroll	#
# kernel.c:137:             dices[i] = diceroll();
	movl	-16(%ebp), %edx	# i, tmp98
	movl	%eax, -116(%ebp,%edx,4)	# _1, dices[i_16]
# kernel.c:136:         for (int i = 0; i < 5; i++) {
	addl	$1, -16(%ebp)	#, i
.L37:
# kernel.c:136:         for (int i = 0; i < 5; i++) {
	cmpl	$4, -16(%ebp)	#, i
	jle	.L38	#,
# kernel.c:139:         yatzy_loop:
	nop	
.L39:
# kernel.c:140:         rollsRemaining--;
	subl	$1, -12(%ebp)	#, rollsRemaining
# kernel.c:141:         prints("Rolls remaining: ");
	subl	$12, %esp	#,
	pushl	$.LC3	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:142:         printi(rollsRemaining);
	subl	$12, %esp	#,
	pushl	-12(%ebp)	# rollsRemaining
	call	printi	#
	addl	$16, %esp	#,
# kernel.c:143:         nl();
	call	nl	#
# kernel.c:144:         prints("Your dices are: ");
	subl	$12, %esp	#,
	pushl	$.LC4	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:145:         for (int i = 0; i < 5; i++) {
	movl	$0, -20(%ebp)	#, i
# kernel.c:145:         for (int i = 0; i < 5; i++) {
	jmp	.L40	#
.L41:
# kernel.c:146:             printc('[');
	subl	$12, %esp	#,
	pushl	$91	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:147:             printi(dices[i]);
	movl	-20(%ebp), %eax	# i, tmp99
	movl	-116(%ebp,%eax,4), %eax	# dices[i_17], _2
	subl	$12, %esp	#,
	pushl	%eax	# _2
	call	printi	#
	addl	$16, %esp	#,
# kernel.c:148:             printc(']');
	subl	$12, %esp	#,
	pushl	$93	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:149:             printc(' ');
	subl	$12, %esp	#,
	pushl	$32	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:145:         for (int i = 0; i < 5; i++) {
	addl	$1, -20(%ebp)	#, i
.L40:
# kernel.c:145:         for (int i = 0; i < 5; i++) {
	cmpl	$4, -20(%ebp)	#, i
	jle	.L41	#,
# kernel.c:151:         nl();
	call	nl	#
# kernel.c:152:         prints("                 ^   ^   ^   ^   ^");
	subl	$12, %esp	#,
	pushl	$.LC5	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:153:         nl();
	call	nl	#
# kernel.c:154:         prints("Dice numbers:    1   2   3   4   5");
	subl	$12, %esp	#,
	pushl	$.LC6	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:155:         nl();
	call	nl	#
# kernel.c:156:         if (rollsRemaining == 0) {
	cmpl	$0, -12(%ebp)	#, rollsRemaining
	je	.L61	#,
# kernel.c:159:         prints("What do you want to do?");
	subl	$12, %esp	#,
	pushl	$.LC7	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:160:         nl();
	call	nl	#
# kernel.c:161:         prints("1 - Reroll");
	subl	$12, %esp	#,
	pushl	$.LC8	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:162:         nl();
	call	nl	#
# kernel.c:163:         prints("2 - Score");
	subl	$12, %esp	#,
	pushl	$.LC9	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:164:         nl();
	call	nl	#
# kernel.c:165:         char c = getch();
	call	getch	#
	movb	%al, -29(%ebp)	# tmp100, c
# kernel.c:166:         char dicesToReRoll[5] = {0};
	movl	$0, -121(%ebp)	#, dicesToReRoll
	movb	$0, -117(%ebp)	#, dicesToReRoll
# kernel.c:167:         int i = 0;
	movl	$0, -24(%ebp)	#, i
# kernel.c:168:         if (c == '1') {
	cmpb	$49, -29(%ebp)	#, c
	jne	.L44	#,
# kernel.c:169:             prints("Which dices to reroll?");
	subl	$12, %esp	#,
	pushl	$.LC10	#
	call	prints	#
	addl	$16, %esp	#,
.L47:
# kernel.c:171:                 dicesToReRoll[i] = getc();
	call	getc	#
# kernel.c:171:                 dicesToReRoll[i] = getc();
	leal	-121(%ebp), %ecx	#, tmp101
	movl	-24(%ebp), %edx	# i, tmp103
	addl	%ecx, %edx	# tmp101, tmp102
	movb	%al, (%edx)	# _3, dicesToReRoll[i_18]
# kernel.c:172:                 printc(dicesToReRoll[i]);
	leal	-121(%ebp), %edx	#, tmp104
	movl	-24(%ebp), %eax	# i, tmp106
	addl	%edx, %eax	# tmp104, tmp105
	movzbl	(%eax), %eax	# dicesToReRoll[i_18], _4
# kernel.c:172:                 printc(dicesToReRoll[i]);
	movsbl	%al, %eax	# _4, _5
	subl	$12, %esp	#,
	pushl	%eax	# _5
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:173:                 if (dicesToReRoll[i] == NEWLINE) {
	leal	-121(%ebp), %edx	#, tmp107
	movl	-24(%ebp), %eax	# i, tmp109
	addl	%edx, %eax	# tmp107, tmp108
	movzbl	(%eax), %eax	# dicesToReRoll[i_18], _6
# kernel.c:173:                 if (dicesToReRoll[i] == NEWLINE) {
	cmpb	$13, %al	#, _6
	je	.L62	#,
# kernel.c:177:                 i++;
	addl	$1, -24(%ebp)	#, i
# kernel.c:171:                 dicesToReRoll[i] = getc();
	jmp	.L47	#
.L62:
# kernel.c:175:                     break;
	nop	
# kernel.c:179:             for (int i = 0; i < 5; i++) {
	movl	$0, -28(%ebp)	#, i
# kernel.c:179:             for (int i = 0; i < 5; i++) {
	jmp	.L48	#
.L57:
# kernel.c:180:                 switch (dicesToReRoll[i]) {
	leal	-121(%ebp), %edx	#, tmp110
	movl	-28(%ebp), %eax	# i, tmp112
	addl	%edx, %eax	# tmp110, tmp111
	movzbl	(%eax), %eax	# dicesToReRoll[i_19], _7
	movsbl	%al, %eax	# _7, _8
# kernel.c:180:                 switch (dicesToReRoll[i]) {
	subl	$48, %eax	#, tmp113
	cmpl	$5, %eax	#, tmp113
	ja	.L49	#,
	movl	.L51(,%eax,4), %eax	#, tmp114
	jmp	*%eax	# tmp114
	.section	.rodata
	.align 4
	.align 4
.L51:
	.long	.L63
	.long	.L55
	.long	.L54
	.long	.L53
	.long	.L52
	.long	.L50
	.text
.L55:
# kernel.c:184:                         dices[0] = diceroll();
	call	diceroll	#
# kernel.c:184:                         dices[0] = diceroll();
	movl	%eax, -116(%ebp)	# _9, dices[0]
# kernel.c:185:                         break;
	jmp	.L49	#
.L54:
# kernel.c:187:                         dices[1] = diceroll();
	call	diceroll	#
# kernel.c:187:                         dices[1] = diceroll();
	movl	%eax, -112(%ebp)	# _10, dices[1]
# kernel.c:188:                         break;
	jmp	.L49	#
.L53:
# kernel.c:190:                         dices[2] = diceroll();
	call	diceroll	#
# kernel.c:190:                         dices[2] = diceroll();
	movl	%eax, -108(%ebp)	# _11, dices[2]
# kernel.c:191:                         break;
	jmp	.L49	#
.L52:
# kernel.c:193:                         dices[3] = diceroll();
	call	diceroll	#
# kernel.c:193:                         dices[3] = diceroll();
	movl	%eax, -104(%ebp)	# _12, dices[3]
# kernel.c:194:                         break;
	jmp	.L49	#
.L50:
# kernel.c:196:                         dices[4] = diceroll();
	call	diceroll	#
# kernel.c:196:                         dices[4] = diceroll();
	movl	%eax, -100(%ebp)	# _13, dices[4]
# kernel.c:197:                         break;
	jmp	.L49	#
.L63:
# kernel.c:182:                         break;
	nop	
.L49:
# kernel.c:179:             for (int i = 0; i < 5; i++) {
	addl	$1, -28(%ebp)	#, i
.L48:
# kernel.c:179:             for (int i = 0; i < 5; i++) {
	cmpl	$4, -28(%ebp)	#, i
	jle	.L57	#,
# kernel.c:200:             goto yatzy_loop;
	jmp	.L39	#
.L44:
# kernel.c:202:         } else if (c == '2') {
	cmpb	$50, -29(%ebp)	#, c
	je	.L64	#,
# kernel.c:131:     while (1) {
	jmp	.L59	#
.L61:
# kernel.c:157:             break;
	nop	
	jmp	.L65	#
.L64:
# kernel.c:203:             break;
	nop	
.L65:
# kernel.c:207: }
	nop	
	movl	-4(%ebp), %edi	#,
	leave	
	.cfi_restore 5
	.cfi_restore 7
	.cfi_def_cfa 4, 4
	ret	
	.cfi_endproc
.LFE10:
	.size	yatzy, .-yatzy
	.section	.rodata
.LC11:
	.string	"Welcome to ManuOS"
.LC12:
	.string	"version"
	.align 4
.LC13:
	.string	"ManuOS ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1, C-edition\n"
.LC14:
	.string	"help"
	.align 4
.LC15:
	.string	"Commands: version, help, wpp, yatzy"
.LC16:
	.string	"wpp"
.LC17:
	.string	"yatzy"
.LC18:
	.string	"y"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
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
# kernel.c:211:     int i = 0;
	movl	$0, -12(%ebp)	#, i
# kernel.c:212:     prints("Welcome to ManuOS");
	pushl	$.LC11	#
	call	prints	#
	addl	$4, %esp	#,
# kernel.c:213:     nl();
	call	nl	#
.L76:
# kernel.c:215:         printc('>');
	subl	$12, %esp	#,
	pushl	$62	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:216:         i = 0;
	movl	$0, -12(%ebp)	#, i
.L70:
# kernel.c:218:             prompt[i] = getc();
	movl	-12(%ebp), %edx	# i, i.1_1
	movl	-16(%ebp), %eax	# prompt, tmp104
	leal	(%edx,%eax), %ebx	#, _2
# kernel.c:218:             prompt[i] = getc();
	call	getc	#
# kernel.c:218:             prompt[i] = getc();
	movb	%al, (%ebx)	# _3, *_2
# kernel.c:219:             printc(prompt[i]);
	movl	-12(%ebp), %edx	# i, i.2_4
	movl	-16(%ebp), %eax	# prompt, tmp105
	addl	%edx, %eax	# i.2_4, _5
	movzbl	(%eax), %eax	# *_5, _6
# kernel.c:219:             printc(prompt[i]);
	movsbl	%al, %eax	# _6, _7
	subl	$12, %esp	#,
	pushl	%eax	# _7
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:220:             if (prompt[i] == NEWLINE) {
	movl	-12(%ebp), %edx	# i, i.3_8
	movl	-16(%ebp), %eax	# prompt, tmp106
	addl	%edx, %eax	# i.3_8, _9
	movzbl	(%eax), %eax	# *_9, _10
# kernel.c:220:             if (prompt[i] == NEWLINE) {
	cmpb	$13, %al	#, _10
	jne	.L67	#,
# kernel.c:221:                 prompt[i] = '\0';
	movl	-12(%ebp), %edx	# i, i.4_11
	movl	-16(%ebp), %eax	# prompt, tmp107
	addl	%edx, %eax	# i.4_11, _12
# kernel.c:221:                 prompt[i] = '\0';
	movb	$0, (%eax)	#, *_12
# kernel.c:222:                 break;
	nop	
# kernel.c:233:         if (m_strcmp(prompt, "version") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC12	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:233:         if (m_strcmp(prompt, "version") == 0) {
	testw	%ax, %ax	# _18
	jne	.L71	#,
	jmp	.L77	#
.L67:
# kernel.c:224:             if (prompt[i] == 0x08) {
	movl	-12(%ebp), %edx	# i, i.5_13
	movl	-16(%ebp), %eax	# prompt, tmp108
	addl	%edx, %eax	# i.5_13, _14
	movzbl	(%eax), %eax	# *_14, _15
# kernel.c:224:             if (prompt[i] == 0x08) {
	cmpb	$8, %al	#, _15
	jne	.L69	#,
# kernel.c:225:                 i--;
	subl	$1, -12(%ebp)	#, i
# kernel.c:226:                 printc(' ');
	subl	$12, %esp	#,
	pushl	$32	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:227:                 printc(0x08);
	subl	$12, %esp	#,
	pushl	$8	#
	call	printc	#
	addl	$16, %esp	#,
# kernel.c:228:                 prompt[i] = '\0';
	movl	-12(%ebp), %edx	# i, i.6_16
	movl	-16(%ebp), %eax	# prompt, tmp109
	addl	%edx, %eax	# i.6_16, _17
# kernel.c:228:                 prompt[i] = '\0';
	movb	$0, (%eax)	#, *_17
.L69:
# kernel.c:230:             i++;
	addl	$1, -12(%ebp)	#, i
# kernel.c:218:             prompt[i] = getc();
	jmp	.L70	#
.L77:
# kernel.c:234:             prints("ManuOS " VERSION "\n");
	subl	$12, %esp	#,
	pushl	$.LC13	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:235:             nl();
	call	nl	#
	jmp	.L76	#
.L71:
# kernel.c:236:         } else if (m_strcmp(prompt, "help") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC14	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:236:         } else if (m_strcmp(prompt, "help") == 0) {
	testw	%ax, %ax	# _19
	jne	.L73	#,
# kernel.c:237:             prints(HELP_MSG);
	subl	$12, %esp	#,
	pushl	$.LC15	#
	call	prints	#
	addl	$16, %esp	#,
# kernel.c:238:             nl();
	call	nl	#
	jmp	.L76	#
.L73:
# kernel.c:239:         } else if (m_strcmp(prompt, "wpp") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC16	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:239:         } else if (m_strcmp(prompt, "wpp") == 0) {
	testw	%ax, %ax	# _20
	jne	.L74	#,
# kernel.c:240:             wpp_interpreter();
	call	wpp_interpreter	#
	jmp	.L76	#
.L74:
# kernel.c:241:         } else if (m_strcmp(prompt, "yatzy") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC17	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:241:         } else if (m_strcmp(prompt, "yatzy") == 0) {
	testw	%ax, %ax	# _21
	jne	.L75	#,
# kernel.c:242:             yatzy();
	call	yatzy	#
	jmp	.L76	#
.L75:
# kernel.c:243:         } else if (m_strcmp(prompt, "y") == 0) {
	subl	$8, %esp	#,
	pushl	$.LC18	#
	pushl	-16(%ebp)	# prompt
	call	m_strcmp	#
	addl	$16, %esp	#,
# kernel.c:243:         } else if (m_strcmp(prompt, "y") == 0) {
	testw	%ax, %ax	# _22
	jne	.L76	#,
# kernel.c:244:             yatzy();
	call	yatzy	#
# kernel.c:215:         printc('>');
	jmp	.L76	#
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
