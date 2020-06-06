GLOBAL cpuVendor
GLOBAL cpuModel
GLOBAL cpuModel1
GLOBAL cpuModel2
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

cpuModel:
	push rbp
	mov rbp, rsp

	push rbx

	mov eax, 80000002h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	pop rbx
	mov rsp, rbp
	pop rbp
	ret

cpuModel1:
	push rbp
	mov rbp, rsp

	push rbx

	mov eax, 80000003h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	pop rbx
	mov rsp, rbp
	pop rbp
	ret

cpuModel2:
	push rbp
	mov rbp, rsp

	push rbx

	mov eax, 80000004h
	cpuid

	mov [rdi], eax		;pongo el string del manufacturer en rdi
	mov [rdi + 4], ebx
	mov [rdi + 8], ecx
	mov [rdi + 12], edx

	mov byte [rdi+16], 0	;termino el string con 0

	mov rax, rdi		;valor de retorno en rax

	pop rbx
	mov rsp, rbp
	pop rbp
	ret