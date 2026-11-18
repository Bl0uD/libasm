global	ft_read							; Export ft_read symbol
extern	__errno_location				; Import libc function for thread-local errno
section	.text							; Executable code section

ft_read:
	mov	rax, 0							; Linux x86-64 syscall: 0 = sys_read
	syscall								; Invoke kernel (rdi = fd, rsi = buf, rdx = count)

	cmp	rax, 0							; Check kernel return value
	jl	.error							; If negative, kernel returned -errno -> handle error

	ret									; Success: rax contains bytes read

.error:
	neg	rax								; Convert negative kernel return (-errno) to positive
	push	rax							; Save positive error code and align RSP to 16 bytes
	call	__errno_location wrt ..plt	; Call libc: returns int* pointer to errno in rax
	pop	rdi								; Restore positive error code into rdi
	mov	[rax], edi						; Store 32-bit error code at address pointed by rax
	mov	rax, -1							; POSIX read: return -1 on error
	ret									; Return -1
