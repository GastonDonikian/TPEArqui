/* sampleCodeModule.c */
#include <stdint.h>
#include <lib.h>
#include "calculator.h"
#include "terminal.h"



int main() {
	//GASTON
	//int c;
	//calculator();
	/*char string[10];
	doubleToString(evaluate("(3.6+3)*3+3+3+3+3+3"),string);
	printf(string);*/

	void(*fun)(void);
	fun = terminal;
	add_program(fun);
	start();
	
	//SEGUNDO
	/*printf("Hola como estas\n");
	printf("Cabeza de alcornoque\n");
	printf("que miras\n");
	changeScreen();
	printf("Todo bien?\n");
	changeScreen();
	printf("ahora volvi\n");*/

	return 0;
}