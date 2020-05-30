GLOBAL secondsRTC
GLOBAL minutesRTC
GLOBAL hoursRTC

section .text

secondsRTC:
	push rbp
	mov rbp, rsp
	mov rax,0x0 ;SETEO TODO EL VALOR DE RETORNO EN 0   000000000000
	out 70h,al ;LE ESCRIBO EN 70H LO QUE QUIERO, QUE ES HYYP://stanislavs.org/helppc/cmos_ram.html segundos
	in al, 71h ;EN EL VALOR DERECHO ME GUARDO LOS SEGUNDOS COMO VA DE 71H SON 8BITS QUE ENTRA EN AX, 
	mov rsp,rbp
	pop rbp  ;COMO LO GUARDE EN AX ESTA TAMBIEN EN RAX PORQUE ANTES LO PUSE EN CERO QUE ES LO QUE SE DEVUELVE,
	ret

minutesRTC:
	push rbp
	mov rbp, rsp
	mov rax,0x2
	out 70h,al
	in al,71h
	mov rsp,rbp
	pop rbp  
	ret

hoursRTC:
	push rbp
	mov rbp, rsp
	mov rax, 0x4
	out 70h,al
	in al,71h
	mov rsp,rbp
	pop rbp 
	ret
