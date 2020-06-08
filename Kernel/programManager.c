
void (* fun_array[2])()={0};
int runningfunc=0;

void addFunction(void (*function)()){
	int i =0;
	if (fun_array[i]!=0){
		i++;
	}
	fun_array[i] = function;
}

void switchFun(){
	if (runningfunc == 0){
		runningfunc =1;
	}
	else{
		runningfunc = 0;
	}
	(fun_array[runningfunc])();
}

void runFunction(){
	(*fun_array[runningfunc])();
}