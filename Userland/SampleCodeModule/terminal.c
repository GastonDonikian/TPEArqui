int i=0;
char bufferTerminal[32];
int DIM = 6;
char * funciones[]= {"help","inforeg","printmem","time","cpuid","cputemp"};
void terminal(){
	setUpDown(1);
	while(1){
		char a;
		while((a=getChar()) !='\n' && a != '\t'){
			putChar(a);
			if(a=='\b' && i!=0){
				bufferTerminal[i-1]=0;
				i--;
			}
			else{
				bufferTerminal[i++]=a;
			}
		}
		if(a=='\n'){
			analize(bufferTerminal);
		}
		else{
			changeScreen();
			return;
		}
	}
}
void analize(char * buffer){
	cleanString(bufferTerminal);
	int flag=0;
	int j;
	for (j = 0; j < DIM && flag == 0; j++){
		flag=stringCmp(funciones[j], bufferTerminal);
	}
	if (flag){
		putChar('\n');
		gotoFunction(j-1);
	}
	else{
		putChar('\n');
		printf("Operacion invalida amigue");
		putChar('\n');
	}
	i = 0;
	for (i = 0;buffer[i]!=0; i++)
	{
		buffer[i]=0;
	}
	i=0;
}
void gotoFunction(int number){
	switch (number) {
		case 0:
			help();
			break;
		case 1:
			inforeg();
			break;
		case 2:
			printmem();
			break;
		case 3:
			gettime();
			break;
		case 4:
			getcpuid();
			break;
		case 5:
			getcputemp();
			break;
	}
	return;
}

void help(){
	for(int i = 0; i< DIM; i++){
		printf(funciones[i]);
		putChar('\n');
	}
}

void inforeg(){}

void printmem(){
	char * pointer= 1200;
	int p =1200;
	char point[11]= {0};
	intToString(p, point);
	printf(point);
}
	/*for (int i = 0; i < 32; i++)
	//{
		//char point[11]={0};
		intToString(p, point);
		p++;
		printf(point);
		putChar(pointer[i]);
		putChar('\n');
	}
	putChar('\n');
} //esto igual esta hecho un can
*/
void gettime(){
	char time[9]={0};
	timeGetter(time);
	printf(time);
	putChar('\n');
}

void getcpuid(){}

void getcputemp(){}