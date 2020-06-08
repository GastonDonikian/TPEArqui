#include "lib.h"
extern void loadFunction(uint64_t *programRegisters,void (*function)(void));

void (* fun_array[2])(void)={0};
int runningfunc=0;

void addFunction(void * func){
	int i =0;
	if (fun_array[i]!=0){
		i++;
	}
	fun_array[i] = func;
	void (*function)(void) = func;
	function();
}

void switchFun(uint64_t rsp){
	programRegisters(rsp,runningfunc);
	if (runningfunc == 0){
		runningfunc =1;
	}
	else{
		runningfunc = 0;
	}
	(fun_array[runningfunc])();
}

void runFunction(){
	void (*function)(void) = fun_array[runningfunc];
	function();
}

void reRunFunction() {
	uint64_t programRegisters[15];
	getProgramRegisters(programRegisters,runningfunc);
	loadFunction(programRegisters,fun_array[runningfunc]);
}