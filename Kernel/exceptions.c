#include <stdint.h>
#include "exceptions.h"
#include "printManager.h"
#include "screenManager.h"
#define ZERO_EXCEPTION_ID 0




void zero_division(uint64_t rsp);

void exceptionDispatcher(int exception,uint64_t rsp) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(rsp);
}

void printRegister(uint64_t reg);

void zero_division(uint64_t rsp) {
	cleanScreen();
	int i = 0;
	char * string = "Trataste de dividir por cero";
	while(string[i] != 0) //imprimo el mensaje de error
		printAnyChar(string[i++],255,0,0);
	printAllRegisters(rsp);
	newLine();


	//printLine("Usted trato de dividir por cero!");
	// Handler para manejar excepcíon
}
void printAllRegisters(uint64_t rsp) {
	uint64_t registerArray[17];
	fetchRegisters(registerArray,rsp); //en rdi tengo rsp y en rsi tengo register
	char * registerNamesArray[] = {"r15","r14","r13","r12","r11","r10","r9","r8","rsp",
	"rdl","rsl","rbp","rdx","rcx","rbx","rax","rip"};
	for(int i = 0; i <18 ;i++ ) {
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
