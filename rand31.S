; http://www.avrfreaks.net/forum/very-fastsmall-random-number-generator
; 31-bit random number
; primitive polynomial order 31
; (1)0100000 10101010 10010101 10110101 (20 AA 95 B5)
; shift before XOR
.global rand_31
rand_31:
	push r24

	lsl	r16			; shift first
	rol	r17
	rol	r18
	rol	r19

	sbrs	r19,7			; test MSB
	rjmp	rand_31_outro			; clear, no XOR

	ldi	r24,0xB5		; first poly byte
	eor	r16,r24			; XOR it in
	ldi	r24,0x95		; second byte of poly
	eor	r17,r24
	ldi	r24,0xAA		; same routine
	eor	r18,r24
	ldi	r24,0x20
	eor	r19,r24

rand_31_outro:
	pop r24
	ret
