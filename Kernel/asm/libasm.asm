GLOBAL cpuVendor
GLOBAL cpuModel1
GLOBAL cpuModel2
GLOBAL fetchRegisters
GLOBAL cpuModel3
GLOBAL cpuTempStatus
GLOBAL cpuTempTarget

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

cpuModel1:
	push rbp
	mov rbp, rsp

	mov eax, 80000002h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax
	
	mov rsp, rbp
	pop rbp
	ret

cpuModel2:
	push rbp
	mov rbp, rsp

	mov eax, 80000003h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	mov rsp, rbp
	pop rbp
	ret

cpuModel3:
	push rbp
	mov rbp, rsp

	mov eax, 80000004h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	mov rsp, rbp
	pop rbp
	ret

cpuTempStatus:
	push rbp
	mov rbp, rsp
						;mov rcx, 0x19C
						;rdmcr
	
	xor rax, rax
	mov eax, 0x88370000
	mov rdi, 0
	mov rdi, rax
	mov rsp, rbp
	pop rbp
	ret

cpuTempTarget:

	push rbp
	mov rbp, rsp
						;mov rcx, 0x1A2
						;rdmcr
	xor rax, rax
	mov eax, 0x690A00
	mov rdi, 0
	mov rdi, rax
	mov rsp, rbp
	pop rbp
	ret


fetchRegisters:
	push rbp
	mov rbp, rsp
	push rax
	mov rax,[rsi]
	mov[rdi],rax 
	mov rax,[rsi +8]
	mov[rdi +8],rax
	mov rax,[rsi +16]
	mov[rdi +16],rax
	mov rax,[rsi +24]
	mov[rdi +24],rax
	mov rax,[rsi +32]
	mov[rdi +32],rax
	mov rax,[rsi +40]
	mov[rdi +40],rax
	mov rax,[rsi +48]
	mov[rdi +48],rax
	mov rax,[rsi +56]
	mov[rdi +56],rax
	mov rax,[rsi +64]
	mov[rdi +64],rax
	mov rax,[rsi +72]
	mov[rdi +72],rax
	mov rax,[rsi +80]
	mov[rdi +80],rax
	mov rax,[rsi +88]
	mov[rdi +88],rax
	mov rax,[rsi +96]
	mov[rdi +96],rax
	mov rax,[rsi +104]
	mov[rdi +104],rax
	mov rax,[rsi +112]
	mov[rdi +112],rax
	mov rax,[rsi +120]
	mov [rdi +120],rax
	mov eax,[rsi + 128] ; accedo al EIP
	mov [rdi +128],eax
	pop rax
	mov rsp, rbp
	pop rbp
	ret

