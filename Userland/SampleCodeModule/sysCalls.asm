section .text
GLOBAL read
GLOBAL write
GLOBAL switchScreen
GLOBAL time
GLOBAL cpuid
GLOBAL cputemp

; void read(char * buf, size_t count)
read:
	mov rax, 0
	int 80h
	ret

; void write(char * buf, size_t count, size_t abajoarriba)
write:
	mov rax, 1
	int 80h
	ret

;void switchScreen()
switchScreen:
	mov rax, 2
	int 80h
	ret

;void time(int * buf)
	mov rax, 3
	int 80h
	ret

;void cpuid(int * buf)
	mov rax, 4
	int 80h
	ret
 ;void	cputemp( * buf)
	mov rax, 5
	int 80h
	ret