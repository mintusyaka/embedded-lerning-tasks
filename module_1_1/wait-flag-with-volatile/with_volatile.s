	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.cpp"
	.text
	.align	2
	.global	_Z9wait_flagPVmt
	.syntax unified
	.arm
	.type	_Z9wait_flagPVmt, %function
_Z9wait_flagPVmt:
	.fnstart
.LFB3:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, [r0]
	tst	r1, r3
	movne	r0, #1
	moveq	r0, #0
	bx	lr
	.cantunwind
	.fnend
	.size	_Z9wait_flagPVmt, .-_Z9wait_flagPVmt
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	.fnstart
.LFB4:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, #1073741824
.L4:
	ldr	r3, [r2]
	tst	r3, #1
	beq	.L4
	mov	r0, #0
	bx	lr
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (Arm GNU Toolchain 15.2.Rel1 (Build arm-15.86)) 15.2.1 20251203"
