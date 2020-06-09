#include <stdint.h>
#include "lib.h"
#include "screenManager.h"
#include "sysCallHandler.h"
#include "time.h"
#include "keyboard.h"
#include "cpuReader.h"
#include "programManager.h"
#include "printManager.h"


void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx,uint64_t r8){ //r8 solo se usa para rsp y multitask
	switch(rcx){
		case 0:
			read((char *) rdi);
			break;
		case 1:
			write(rdi, rsi, rdx);
			break;
		case 2:
			switchScreen();
			break;
		case 3:
			time((char *)rdi);
			break;
		case 4:
			cpuGetter((char *)rdi);
			break;
		case 5:
			cputemp((char *)rdi);
			break;
		case 6:
			registerInfo((uint64_t *)rdi);
			break;
		case 7:
			add_Program((void(*)(void))rdi);
			break;
		case 8:
			startProgram(r8);
			break;
	}
	return;
}

void read(char * buffer) {
	keyboard_reader(buffer);
}

void write(uint64_t buffer, uint64_t count, uint64_t upordown){
	if(count <= 0 || (upordown != 0 && upordown != 1))
		return;
	screenWriter((char *)buffer, count, upordown);
}

void switchScreen() {
	selector();
}

void time(char * buffer){
	timeGetter(buffer);
}

void cpuGetter(char * buffer) {
	cpuModel(buffer);
}

void cputemp(char * buffer){
	cpuTemperature(buffer);
}

void registerInfo(uint64_t * buffer) {
	getCurrentRegisters(buffer);
}

void add_Program(uint64_t function){
	//((void(*)(void))function)();
	addFunction((void(*)(void))function);
}

void startProgram(uint64_t rsp){
	initializeFunction(rsp);
}