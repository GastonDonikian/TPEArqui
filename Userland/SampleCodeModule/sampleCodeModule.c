/* sampleCodeModule.c */
#include <stdint.h>
#include <lib.h>
#include "calculator.h"
#include "terminal.h"



int main() {
	void(*fun)(void);
	fun = terminal;
	add_program(fun);
	fun = calculator;
	add_program(fun);
	start();
	return 0;
}