section .text
GLOBAL invalidOpCode
GLOBAL ceroDiv


invalidOpCode:
	ud2
	ret

ceroDiv:
	push rbp
	mov rbp, rsp
	mov EAX, 3
	mov EBX, 0
	DIV EBX

	mov rsp, rbp
	pop rbp
	ret

