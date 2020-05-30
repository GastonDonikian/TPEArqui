GLOBAL keyPressed
GLOBAL getKey

section .text

keyPressed:
	in al,64h
	and al,0x01 ;EN EL PRIMER BIT ESTA SI TIENE INFORMACION PARA MI O NO	
	ret

getKey:
	in al,60h
	ret