#include <stdint.h>
#include "screenManager.h"
extern char * cpuModel();
extern char * cpuModel1();
extern char * cpuModel2();

sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	switch(rcx){
		case 0:
			read(rdi);
			break;
		case 1:
			write(rdi, rsi, rdx);
			break;
		case 2:
			switchScreen();
			break;
		case 3:
			time(rdi);
			break;
		case 4:
			cpuGetter(rdi);
			break;
		case 5:
			cputemp(rdi);
			break;

	}
	return;
}

void read(uint64_t buffer) {
	keyboard_reader(buffer);
}

void write(uint64_t buffer, uint64_t count, uint64_t upordown){
	screenWriter(buffer, count, upordown);
}

void switchScreen() {
	selector();
}

void time(uint64_t buffer){
	timeGetter(buffer);
}

void cpuGetter(char * buffer) {
	printLine(buffer);
	char * aux;
	aux = cpuModel();
	printLine(aux);
	printLine(buffer);
	for (int i = 0; i < 16; ++i)
	{
		buffer[i] = aux[i];
	}
	printLine(buffer);
	aux = cpuModel1();
	printLine(aux);
	for (int i = 0; i < 16; ++i)
	{
		buffer[(i+16)] = aux[i];
	}
	printLine(buffer);
	aux = cpuModel2();
	printLine(aux);
	for (int i = 0; i < 16; ++i)
	{
		buffer[i+32] = aux[i];
	}
	printLine(buffer);
	
}

void cputemp(uint64_t buffer){
	//getTemp(buffer);
}