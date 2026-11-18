global	ft_strcpy			; Export ft_strcpy symbol
section	.text				; Executable code section

ft_strcpy:
	mov	rax, rdi			; Save destination pointer in rax (return value)

.loop:
	mov	dl, [rsi]			; Load byte from source into 8-bit register dl
	mov	[rdi], dl			; Store byte into destination buffer
	inc	rsi					; Advance source pointer
	inc	rdi					; Advance destination pointer
	cmp	dl, 0				; Check if copied byte is null terminator '\0'
	je	.end				; If end of string, exit loop
	jmp	.loop				; Repeat loop

.end:
	ret						; Return original destination pointer in rax
