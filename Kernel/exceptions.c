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
void exception(char * string,uint64_t rsp) {
	cleanScreen();
	setUpDown(0);
	int i = 0;
	while(string[i] != 0) //imprimo el mensaje de error
		printAnyChar(string[i++],255,0,0);
	printAllRegisters(rsp);
	newLine();
	initializeFunction(rsp);
}
void invalid_operation_code(uint64_t rsp) {
	exception("Invalid Operation Code",rsp);
}

void zero_division(uint64_t rsp) {
	exception("Trataste de dividir por cero",rsp);

}
