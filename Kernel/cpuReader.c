#include <stdint.h>
#include "lib.h"

extern char * cpuModel1(char * buffer);
extern char * cpuModel2(char * buffer);
extern char * cpuModel3(char * buffer);
extern uint64_t cpuTempStatus();
extern uint64_t cpuTempTarget();
 
void cpuModel(char * result){
	char aux[16] = {0};
	cpuModel1(result);
	cpuModel2(aux);
	for (int i = 16; aux[i%16] != 0; i++)
	{
		result[i] = aux[i%16];
	}
	cpuModel3(aux);
	for (int i = 32; aux[i%16] != 0; i++)
	{
		result[i] = aux[i%16];
	}
} 

void cpuTemperature(char * result){
	uint64_t tempStatus = cpuTempStatus();
	uint64_t tempTarget = cpuTempTarget();
	uint64_t cpuTemp;
	tempStatus = tempStatus >> 16;

	tempStatus = tempStatus & 0x7F;
	uint64_t offset = tempTarget >> 24;
	offset = offset & 0x3F;
	tempTarget = tempTarget >> 16;
	tempTarget = tempTarget & 0xFF;
	tempTarget += offset;
	cpuTemp = (tempTarget - tempStatus);
	intToString(cpuTemp, result);
}