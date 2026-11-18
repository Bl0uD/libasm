global	ft_calloc						; Export ft_calloc symbol
extern	malloc							; Import libc malloc for heap allocation
extern	__errno_location				; Import libc function for thread-local errno
section	.text							; Executable code section

ft_calloc:
	mov	rax, rdi						; Move number of elements (nmemb) into rax
	mul	rsi								; Compute total size: rax = nmemb * size
	jc	.overflow						; If carry flag is set, multiplication overflowed size_t

	mov	rdi, rax						; Place total size into rdi (1st arg for malloc)
	push	rdi							; Save total size on stack and align RSP to 16 bytes
	call	malloc wrt ..plt			; Allocate memory (pointer returned in rax)
	pop	rdi								; Restore total size into rdi
	test	rax, rax					; Check if malloc returned NULL
	jz	.error							; If allocation failed, return NULL

	xor	rcx, rcx						; Initialize index counter to 0

.loop:
	cmp	rcx, rdi						; Check if counter reached total size
	je	.end							; If all bytes are zeroed, finish
	mov	byte [rax + rcx], 0				; Set current byte to 0
	inc	rcx								; Move to next byte
	jmp	.loop							; Repeat loop

.overflow:
	sub	rsp, 8							; Align RSP to 16 bytes before function call
	call	__errno_location wrt ..plt	; Get pointer to errno in rax
	add	rsp, 8							; Restore RSP
	mov	dword [rax], 12					; Set errno = ENOMEM (12 on Linux)
	xor	rax, rax						; Return NULL
	ret

.error:
	xor	rax, rax						; Return NULL
	ret

.end:
	ret									; Return pointer to zeroed allocated block in rax
