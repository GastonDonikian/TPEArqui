#include <stdint.h>
#include "lib.h"
#include "screenManager.h"
#include "sysCallHandler.h"

void add_Program(void * func);

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
		case 6:
			registerInfo(rdi);
			break;
		case 7:
			add_Program(rdi);
			break;
		case 8:
			startProgram();
			break;
	}
	return;
}

void read(uint64_t buffer) {
	keyboard_reader(buffer);
}

void write(uint64_t buffer, uint64_t count, uint64_t upordown){
	if(count <= 0 || (upordown != 0 && upordown != 1))
		return;
	screenWriter(buffer, count, upordown);
}

void switchScreen() {
	selector();
}

void time(uint64_t buffer){
	timeGetter(buffer);
}

void cpuGetter(uint64_t buffer) {
	cpuModel(buffer);
}

void cputemp(uint64_t buffer){
	cpuTemperature(buffer);
}

void registerInfo(uint64_t * buffer) {
	getCurrentRegisters(buffer);
}

void add_Program(void * func){
	addFunction(func);
}

void startProgram(){
	runFunction();
}