#include <stdint.h>

extern char * cpuModel1(char * buffer);
extern char * cpuModel2(char * buffer);
extern char * cpuModel3(char * buffer);
extern uint64_t cpuTempStatus();
extern uint64_t cpuTempTarget();

void intToString(uint64_t num, char * result){
	int i =0;
	while(num !=0){
		result[i++]= num%10 + '0';
		num = num/10;
	}
	int j=0;
	char aux;
	while (j<(i/2)){
		aux = result[j];
		result[j] = result[i-1-j];
		result[i-1-j]= aux;
		j++;
	}
	return;
	result[i]=0;
} 
void cpuModel(char * result){
	cpuModel1(result);
	cpuModel2(result + 16);
	cpuModel3(result + 32);
} 

int cpuTemperature(char * result){
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