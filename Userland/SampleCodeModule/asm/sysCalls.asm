section .text
GLOBAL read
GLOBAL write
GLOBAL switchScreen
GLOBAL time
GLOBAL getCpuid
GLOBAL cputemp
GLOBAL getRegisters
GLOBAL addProgram
GLOBAL startRunning

; void read(char * buf)
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

;void time(char * buf)
time:
	mov rax, 3
	int 80h
	ret

;void getCpuid(char * buf)
getCpuid:
	mov rax, 4
	int 80h
	ret


 ;void	cputemp(char * buf)
cputemp:
	mov rax, 5
	int 80h
	ret

;void getRegisters(uint64_t * registerKeeper)
getRegisters:	
	mov rax,6
	int 80h
	ret

;void addProgram(void (* fun)())
addProgram:
	mov rax, 7
	int 80h
	ret

; void startRunning
startRunning:
	mov rax, 8
	int 80h
	ret