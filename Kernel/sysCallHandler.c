#include <stdint.h>

sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	switch(rcx){
		case 0:
			read(rdi, rsi);
			break;
		case 1:
			write(rdi, rsi, rdx);
			break;
		case 2:
			switchScreen(rdi);
			break;
		case 3:
			time(rdi);
			break;
		case 4:
			cpuid(rdi);
			break;
		case 5:
			cputemp(rdi);
			break;
	}
	return;
}

void read(uint64_t buffer, uint64_t count) {
	keyboard_reader(buffer, count);
}

void write(uint64_t buffer, uint64_t count, uint64_t upordown){
	screenWriter();
}

void switchScreen(uint64_t side) {
	timer_handler();
}

void time(uint64_t buffer){
	timeGetter(buffer);
}
void cpuid(uint64_t buffer) {
	timer_handler();
}

void cputemp(uint64_t buffer){
	keyboard_handler();
}