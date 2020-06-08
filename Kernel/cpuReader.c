#include <stdint.h>
#include "lib.h"

extern char * cpuModel1(char * buffer);
extern char * cpuModel2(char * buffer);
extern char * cpuModel3(char * buffer);
extern uint64_t cpuTempStatus();
extern uint64_t cpuTempTarget();
 
void cpuModel(char * result){
	cpuModel1(result);
	cpuModel2(result + 16);
	cpuModel3(result + 32);
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