		.data		;
counter:	.word 0		;

	.text		;
jt:	.word case0	;
	.word case1	;
	.word case2	;
	.word case3	;
	.word case4	;
	.word case5	;
	.word case6	;

	.global mario
mario:	cmp #7, &counter	;
	mov &counter, r12	;
	add r12, r12		;
	mov jt(r12), r0		;
case0:
case1:
case2:
case4:	mov #750, r12		;
	call #buzzer_set_period	;
	add #1, &counter	;
	jmp end			;
case3:	mov #950, r12		;
	call #buzzer_set_period	;
	add #1, &counter	;
	jmp end			;
case5:	mov #630, r12		;
	call #buzzer_set_period	;
	add #1, &counter	;
	jmp end			;
case6:	mov #1260, r12		;
	call #buzzer_set_period	;
	mov #0, &counter	;
	jmp end			;
end:	pop r0			;
return
