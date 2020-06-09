#ifndef _programManager
#define _programManager
void addFunction(void (*function)());
void switchFun();
void initializeFunction();
void reRunFunction();
void loadFunction(uint64_t *registers,void (*function)(void));
#endif