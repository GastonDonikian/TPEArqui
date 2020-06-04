/* sampleCodeModule.c */
#include <stdint.h>
#include <lib.h>
#include "calculator.h"

#define EPSILON 0.0001
void read(char * buf, uint64_t count);
void write(char * buf, uint64_t count, uint64_t abajoarriba);



int main() {
	printf("Cabeza de termo\n");
	double doub = 2.7111;
	if(stringToDouble("2.7113") - doub < EPSILON)
		printf("funciono\n");
	return 0;
}