#ifndef _exceptions
#define _exceptions 
void exceptionDispatcher(uint64_t exception,uint64_t rsp);
void zero_division();
void printAllRegisters(uint64_t rsp);
int tryAndContinue();
#endif
