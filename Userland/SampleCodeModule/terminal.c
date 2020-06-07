
#include "terminal.h"

int longitud=0;
char bufferTerminal[48] = {0};
char * postBuffer;
int DIM = 6;
char * funciones[]= {"help","inforeg","printmem","time","cpuid","cputemp"};


void removePostSpaces(char * string); //LAS AGREGO ACA PORQUE COMO NO ESTAN EN EL .H
void removePreSpaces(char * string); //TIRAN WARNINGS

void terminal(){
	setUpDown(1);
	while(1){
		char a;
		while((a=getChar()) !='\n' && a != '\t'){
			if(a=='\b'){
				if(longitud!=0){
					bufferTerminal[longitud-1]=0;
					longitud--;
					putChar(a);
				}
			}
			else{
				putChar(a);
				bufferTerminal[longitud++]=a;
			}
		}
		if(a=='\n'){
			putChar(a);
			analize(bufferTerminal);
		}
		if (a=='\t'){
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
		gotoFunction(j-1, postBuffer);
	}
	else{
		putChar('\n');
		printf("Operacion invalida");
		putChar('\n');
	}
	for (int i = 0;buffer[i]!=0; i++){
		buffer[i]=0;
	}
	longitud=0;
	for (int k = 0; postBuffer[k]!= 0; k++){
		postBuffer[k]=0;
	}
}

void gotoFunction(int number, char * postBuffer){
	switch (number) {
		case 0:
			help();
			break;
		case 1:
			inforeg();
			break;
		case 2:
			printmem(postBuffer);
			break;
		case 3:
			gettime();
			break;
		case 4:
			getid();
			break;
		case 5:
			cpuTemperature();
			break;
	}
	return;
}

void resetBufferTerminal(){
	for (int i = 0; i < 48; i++){
		bufferTerminal[i]=0;
	}
	longitud=0;
}

void help(){
	for(int i = 0; i< DIM; i++){
		printf(funciones[i]);
		putChar('\n');
	}
}

void inforeg(){}

void printmem(char * pointString){
	cleanString(pointString);
	int pointInt = stringToInt(pointString);
	char * pointer = pointInt;
	for (int i = 0; i < 32; i++)
	{
		char p[11]={0};
		intToString(pointInt, p);
		pointInt++;
		printf(p);
		putChar('\t');
		char memorystring[8]={0};
		charToBits(pointer[i], memorystring);
		printf(memorystring);
		putChar('\n');
	}
}

void gettime(){
	char time[9]={0};
	timeGetter(time);
	printf(time);
	putChar('\n');
}

void getid(){
	char cpuAns[48] = {0};
	getCpu(cpuAns);
	printf(cpuAns);
	putChar('\n');
	resetBufferTerminal();
	terminal();
}

void cpuTemperature(){
	char result[20]={0};
	getCpuTemp(result);
	printf(result);
	putChar('\n');
}

void cleanString(char * string){
	removePreSpaces(string);
	removePostSpaces(string);
}

void removePreSpaces(char * string){
	int i;
	for (i=0; string[i]==' '; i++){
	}
	if(i>0){
		int j=0;
		while(string[i]!=0){
			string[j++]=string[i++];
		}
	}
}

void removePostSpaces(char * string){
	for (int i = 0; string[i]!=0; i++){
		if(string[i]==' '){
			string[i]=0;
			i +=1;
			postBuffer = string + i;
			return;
		}
	}
}