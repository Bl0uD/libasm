global	ft_strdup						; Export ft_strdup symbol
extern	ft_strlen						; Import ft_strlen to compute source length
extern	ft_strcpy						; Import ft_strcpy to copy source string
extern	malloc							; Import libc malloc for heap allocation
section	.text							; Executable code section

ft_strdup:
	push	rdi							; Save source pointer and align RSP to 16 bytes
	call	ft_strlen					; Measure source string length (returned in rax)
	inc	rax								; Add 1 byte for null terminator '\0'
	mov	rdi, rax						; Set allocation size as 1st argument for malloc
	call	malloc wrt ..plt			; Allocate memory on the heap (returned in rax)
	test	rax, rax					; Check if malloc returned NULL
	jz	.error							; If allocation failed, jump to error handler

	pop	rsi								; Restore source string pointer into rsi (2nd arg)
	mov	rdi, rax						; Set allocated buffer as rdi (1st arg)
	call	ft_strcpy					; Copy string into new buffer (returns buffer in rax)
	ret									; Return pointer to duplicated string in rax

.error:
	pop	rdi								; Clean stack (restore pushed source pointer)
	ret									; Return NULL (rax is already 0)
