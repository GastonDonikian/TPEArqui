section .text
GLOBAL invalidOpCode
GLOBAL ceroDiv


invalidOpCode:
	ud2
	ret

ceroDiv:
	mov eax, 3
	mov ebx, 0
	div ebx
	ret