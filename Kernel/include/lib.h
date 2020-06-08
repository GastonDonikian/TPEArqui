#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
char *cpuVendor(char *result);
void printAllRegisters(uint64_t rsp);
void printRegister(uint64_t reg);
void getCurrentRegisters(uint64_t *buffer);
void currentRegisters(uint64_t rsp);
void programRegisters(uint64_t rsp,int program);
void getProgramRegisters(uint64_t *buffer,int program);
#endif