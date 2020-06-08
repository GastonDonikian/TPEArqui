#ifndef _exceptions
#define _exceptions 
void exceptionDispatcher(int exception,uint64_t rsp);
void zero_division();
void printAllRegisters(uint64_t rsp);
int tryAndContinue();
#endif
