#include "lib.h"
#include "programManager.h"
#include "printManager.h"

extern void asmRunFunction(uint64_t *programRegisters,void (*function)(void),uint64_t *stack,uint64_t rsp);
#define STACKSIZE 512
void (* fun_array[2])(void)={0};
int runningfunc=0;
uint64_t stackProgram[2][STACKSIZE];



void addFunction(void * func){
	int i =0;
	while (fun_array[i]!=0){
		i++;
	}
	fun_array[i%2] = func;
}

void switchFun(uint64_t rsp){
	programRegisters(rsp,runningfunc);

	if (runningfunc == 0){
		runningfunc =1;
	}
	else{
		runningfunc = 0;
	}
	selector();
	initializeFunction(rsp);
}

void initializeFunction(uint64_t rsp){
	uint64_t programRegisters[16];
	getProgramRegisters(programRegisters,runningfunc);
	asmRunFunction(programRegisters,fun_array[runningfunc],(stackProgram[runningfunc] + STACKSIZE),rsp); //LOS REGISTROS A CARGAR, LA FUNCION A CORRER, EL STACK Y LA POSICION
}

