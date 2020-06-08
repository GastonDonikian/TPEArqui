#ifndef _sysCallHandler_
#define _sysCallHandler_

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);
void read(char * buffer);
void write(uint64_t buffer, uint64_t count, uint64_t upordown);
void switchScreen();
void time(char * buffer);
void cpuGetter(uint64_t buffer);
void cputemp(uint64_t buffer);
void registerInfo(uint64_t * buffer);
void add_Program(void * func);
void startProgram();

#endif