global	ft_strlen			; Export ft_strlen symbol
section	.text				; Executable code section

ft_strlen:
	xor	rax, rax			; Initialize counter (and return value) to 0

.loop:
	cmp	byte [rdi + rax], 0	; Check if byte at current index is null terminator '\0'
	je	.end				; If null terminator found, jump to end
	inc	rax					; Increment length counter
	jmp	.loop				; Repeat loop

.end:
	ret						; Return length in rax
