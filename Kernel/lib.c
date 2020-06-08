#include <stdint.h>
#include "lib.h"
#include "printManager.h"
uint64_t registerKeeper[15];

extern void fetchRegisters(uint64_t * array,uint64_t stackDirection);

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void currentRegisters(uint64_t rsp) {
	fetchRegisters(registerKeeper,rsp);
}
void getCurrentRegisters(uint64_t *buffer) {
	for(int i = 0; i <15;i++) {
		buffer[i]= registerKeeper[i];
	}
}

void printAllRegisters(uint64_t rsp) {
	uint64_t registerArray[16];
	fetchRegisters(registerArray,rsp); //en rdi tengo rsp y en rsi tengo register
	char * registerNamesArray[] = {"r15","r14","r13","r12","r11","r10","r9","r8","rsi",
	"rdi","rbp","rdx","rcx","rbx","rax","rip"};
	for(int i = 0; i <16 ;i++ ) {
		newLine();
		int j = 0;
		while(registerNamesArray[i][j] != 0) {
			printAnyChar(registerNamesArray[i][j++],255,0,0);
		}
		if(j == 2)
			printAnyChar(' ',255,0,0);
		printAnyChar(' ',255,0,0);
		printRegister(registerArray[i]);
		
	}
}
void printRegister(uint64_t reg) {
	char array[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char aux;
	for(int i = 0; i < 16;i++) { 
		aux = (reg & 0xF000000000000000) >> 60; 
		reg = reg << 4;
		printAnyChar(array[aux],255,0,0);
	}
	printAnyChar('h',255,0,0);

	return;
}

void intToString(uint64_t num, char * result){
	int i =0;
	while(num !=0){
		result[i++]= num%10 + '0';
		num = num/10;
	}
	int j=0;
	char aux;
	while (j<(i/2)){
		aux = result[j];
		result[j] = result[i-1-j];
		result[i-1-j]= aux;
		j++;
	}
	return;
	result[i]=0;
}
