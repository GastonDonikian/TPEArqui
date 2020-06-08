#include <stdint.h>
#include "lib.h"
#include "exceptions.h"
#include "printManager.h"
#include "programManager.h"
#include "screenManager.h"
#include "sysCallHandler.h"
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE 6
void zero_division(uint64_t rsp);
void invalid_operation_code(uint64_t rsp);


void exceptionDispatcher(int exception,uint64_t rsp) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(rsp);
	else if(exception == INVALID_OP_CODE)
		invalid_operation_code(rsp);
}

//void printRegister(uint64_t reg);

void invalid_operation_code(uint64_t rsp) {
	cleanScreen();
	setUpDown(0);
	int i = 0;
	char * string = "Invalid Operation Code";
	while(string[i] != 0) //imprimo el mensaje de error
		printAnyChar(string[i++],255,0,0);
	printAllRegisters(rsp);
	newLine();
	if(tryAndContinue()) {
		reRunFunction();
	}
	else;
		//NO SE QUE HACER ACA! PARA QUE NO SIGA CORRIENDO MI PROGRAMA
}
void zero_division(uint64_t rsp) {
	cleanScreen();
	setUpDown(0);
	int i = 0;
	char * string = "Trataste de dividir por cero";
	while(string[i] != 0) //imprimo el mensaje de error
		printAnyChar(string[i++],255,0,0);
	printAllRegisters(rsp);
	newLine();
	if(tryAndContinue()) {
		cleanScreen();
		//reRunFunction();
	}
	else
		cleanScreen();
	//printLine("Usted trato de dividir por cero!");
	// Handler para manejar excepcíon
}

int tryAndContinue() {
	setUpDown(1);
	print("Try to Continue? Y/n");
	char a = 0;
	while(a==0){
		read(&a);
	}
	return (a == 'y');
}