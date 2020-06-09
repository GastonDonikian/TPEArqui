GLOBAL cpuVendor
GLOBAL cpuModel1
GLOBAL cpuModel2
GLOBAL fetchRegisters
GLOBAL cpuModel3
GLOBAL cpuTempStatus
GLOBAL cpuTempTarget
GLOBAL loadFunction
GLOBAL asmRunFunction

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
	
	push rbx
	push rcx
	push rdx

	mov eax, 80000002h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	pop rdx
	pop rcx
	pop rbx

	mov rax, rdi		;valor de retorno en rax
	
	mov rsp, rbp
	pop rbp
	ret

cpuModel2:
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push rdx

	mov eax, 80000003h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	pop rdx
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp
	ret

cpuModel3:
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push rdx

	mov eax, 80000004h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	pop rdx
	pop rcx
	pop rbx

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

loadFunction:
	mov r15,[rdi]
	mov r14,[rdi + 8]
	mov r13, [rdi+16]
	mov r12,[rdi +24]
	mov r11,[rdi +32]
	mov r10,[rdi+40]
	mov r9,[rdi+48]
	mov r8,[rdi+56]
	;mov rsi,[rdi+64] esta no
	mov rbp,[rdi+80]
	mov rdx,[rdi+88]
	mov rcx,[rdi+96]
	mov rbx,[rdi+104]
	mov rax,[rdi+112]
	mov rdi,[rdi+72]
	jmp rsi



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

	mov rax,[rsi + 120] ; accedo al RIP
	mov [rdi +120],rax
	pop rax
	mov rsp, rbp
	pop rbp
	ret

asmRunFunction:
	;rdi = programRegisters, tengo 15 programRegisters[0]
	;rsi = puntero a funcion que correr
	;rdx = posicion en el stack
	;rcx = rsp del stack
	push rax

	mov rax,[rdi] ; 1 r15
	mov [rcx],rax

	mov rax,[rdi+8] ;2 r14
	mov [rcx+8],rax

	mov rax,[rdi+16] ;3 r13
	mov [rcx+16],rax
	
	mov rax,[rdi+24] ;4 r12
	mov [rcx+24],rax
	
	mov rax,[rdi+32] ;5 r11
	mov [rcx+32],rax
	
	mov rax,[rdi+40] ; 6 r10
	mov [rcx+40],rax
	
	mov rax,[rdi+48] ;7 r9
	mov [rcx+48],rax
	
	mov rax,[rdi+56] ;8 r8
	mov [rcx+56],rax
	
	mov rax,[rdi+64] ;9 rsi
	mov [rcx+64],rax
	
	mov rax,[rdi+72] ;10 rdi
	mov [rcx+72],rax

	mov rax,[rdi+80] ;11 rbp
	mov [rcx+80],rax
	
	mov rax,[rdi+88] ;12 rdx
	mov [rcx+88],rax
	
	mov rax,[rdi+96] ;13 rcx
	mov [rcx+96],rax
	
	mov rax,[rdi+104] ;14 rbx
	mov [rcx+104],rax
	
	mov rax,[rdi+112] ;15 rax
	mov [rcx+112],rax

	;ya cargue todos los registros del programa

	mov [rcx+120],rsi ;cargo la funcion en RIP
	mov [rcx+144], rdx ;le cargo el stack de su programa
	pop rax
	ret



	


