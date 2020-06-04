/* sampleCodeModule.c */
#include <stdint.h>
#include <lib.h>
void terminal();
void read(char * buf, uint64_t count);
void write(char * buf, uint64_t count, uint64_t abajoarriba);



int main() {
	terminal();
	printf("Hola como estas\n");
	printf("Cabeza de alcornoque\n");
	printf("que miras\n");
	changeScreen();
	printf("Todo bien?\n");
	changeScreen();
	printf("ahora volvi\n");
	return 0;
}