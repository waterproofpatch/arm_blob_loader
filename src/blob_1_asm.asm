.text
.global _start
_start:
	mov r0, #0
	mov r1, #0
loop:
	mov r0, #1
	add r1, r1, r0
	ldr r2, =0xdeadbeef
	cmp r1, r2
	bne loop
done:
	mov r1, #0
	b loop
