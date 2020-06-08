/* sampleCodeModule.c */
#include <stdint.h>
#include <lib.h>
#include "calculator.h"
#include "terminal.h"

#define EPSILON 0.0001



int main() {
	//GASTON
	//int c;
	//calculator();
	void (*terminal_ptr)() = &terminal;
	add_program(terminal_ptr);
	start();
	terminal();
	/*char string[10];
	doubleToString(evaluate("(3.6+3)*3+3+3+3+3+3"),string);
	printf(string);*/
	
	
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