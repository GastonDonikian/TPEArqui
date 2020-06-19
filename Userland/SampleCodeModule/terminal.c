#include <stdint.h>
#include "lib.h"
#include "terminal.h"
#define TERMINALDIM  100
#define DIM 8

extern void getRegisters(long int registerKeeper[]);
extern void invalidOpCode();
extern void ceroDiv();

int firstTime = 1;
int enter = 0;
int longitud = 0;
char bufferTerminal[TERMINALDIM] = {0};
char * postBuffer;
char * funciones[DIM]= {"help","inforeg","printmem","time","cpuid","cputemp","ceroDiv", "invalidOp"};

void terminal(){
	setUpDown(1);
	if(firstTime){
		firstTime = 0;
		printf("Bienvenido, usted se encuentra\n en el Shell.\n\n");
		printf("Puede ver los comandos con el\n comando help.\n\n");
		printf("Apriete tab para cambiar a la\n calculadora, y esc para guardar el estado de los registros\n");
		putChar('\n');
	}
	while(1){
		if(!enter){
			printf("<user/shell>:");
			enter = 1;
		}
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
				if(longitud >= TERMINALDIM){
					putChar('\n');
					printf("no hay espacio en la terminal, escriba su comando devuelta");
					putChar('\n');
					for (int i = 0;bufferTerminal[i]!=0; i++){
						bufferTerminal[i]=0;
					}
					longitud=0;

				}
				else{
					putChar(a);
					bufferTerminal[longitud++]=a;
				}
			}
		}
		if(a=='\n'){
			putChar(a);
			enter = 0;	
			analize(bufferTerminal);
		}
	}
}

void analize(char * buffer){
	cleanString(buffer);
	int flag=0;
	int j;
	for (j = 0; j < DIM && flag == 0; j++){
		flag=stringCmp(funciones[j], buffer);
	}
	if (flag){
		putChar('\n');
		gotoFunction(j-1, postBuffer);
		putChar('\n');
	}
	else{
		putChar('\n');
		printf("Debe ingresar un comando");
		putChar('\n');
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
		case 6:
			ceroDivision();
			break;
		case 7:
			invalidOperation();
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

void inforeg(){
	long int registerKeeper[34];
	getRegisters(registerKeeper);
	printAllRegisters(registerKeeper);
	putChar('\n');
}

void printmem(char * pointString){
	cleanString(pointString);
	int j = 0;
	if (pointString[j] == 0){
		printf("Debe indacarme la posicion de memoria a imprimir en formato int");
		return;
	}
	while(pointString[j]!=0){
		if(pointString[j]<'0'|| pointString[j]>'9'){
			printf("la direccion de memoria debe estar en formato int");
			putChar('\n');
			return;
		}
		j++;
	}
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
	putChar('\n');
	resetBufferTerminal();
	terminal();
}

void cpuTemperature(){
	char result[20]={0};
	getCpuTemp(result);
	printf(result);
	printf(" grados Celsius");
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

void ceroDivision(){
	longitud = 0;
	bufferTerminal[0] = 0;
	resetBufferTerminal();
	ceroDiv();
}

void invalidOperation(){
	longitud = 0;
	bufferTerminal[0] = 0;
	resetBufferTerminal();
	invalidOpCode();
}