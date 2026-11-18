global	ft_strcmp			; Export ft_strcmp symbol
section	.text				; Executable code section

ft_strcmp:
	xor	rax, rax			; Clear rax for return value

.loop:
	mov	al, [rdi]			; Load byte from first string into al
	mov	dl, [rsi]			; Load byte from second string into dl
	cmp	al, dl				; Compare the two bytes
	jne	.not_equal			; If they differ, jump to difference calculation
	cmp	al, 0				; Check if current byte is null terminator '\0'
	je	.equal				; If '\0', both strings reached end identically
	inc	rdi					; Advance first string pointer
	inc	rsi					; Advance second string pointer
	jmp	.loop				; Repeat loop

.not_equal:
	movzx	eax, al			; Zero-extend first byte to 32-bit unsigned
	movzx	edx, dl			; Zero-extend second byte to 32-bit unsigned
	sub	eax, edx			; Subtract (unsigned char)s1 - (unsigned char)s2
	ret						; Return difference in eax (rax)

.equal:
	ret						; Return 0 in rax
