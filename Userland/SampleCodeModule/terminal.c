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
char  * postBuffer = bufferTerminal;
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
					printf("Se lleno el buffer.\n");
					putChar('\n');
					clearBufferTerminal();
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
		char auxPost[30] = {0};
		for (int i = 0; postBuffer[i] != 0 && i < 30; i++){
			auxPost[i] = postBuffer[i];
		}
		clearBufferTerminal();
		gotoFunction(j-1, auxPost);
		putChar('\n');
	}
	else{
		putChar('\n');
		printf("Debe ingresar un comando");
		putChar('\n');
		putChar('\n');
		clearBufferTerminal();
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
void charToHex(char  bits,char * string) {
	unsigned char array[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i = 0; i < 2;i++) { 
		string[1 - i] = array[(bits & 0xF)]; 
		bits = bits >> 4;
	}
	string[2] = 0;
	return;
	
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
	long int pointInt = stringToLong(pointString);
	char * pointer = (char *)pointInt;
	printf("\nPOS\t BITS     HEX ASCII\n\n");
	for (int i = 0; i < 32; i++)
	{
		char p[11]={0};
		longToString(pointInt, p);
		pointInt++;
		printf(p);
		putChar('\t');
		char memorystring[8]={0};
		charToBits(pointer[i], memorystring);
		printf(memorystring);
		putChar(' ');
		charToHex(pointer[i], memorystring);
		printf(memorystring);
		putChar('h');
		putChar(' ');
		putChar(pointer[i]);
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
		string[j] = 0;
	}
}

void removePostSpaces(char * string){
	int flag = 1;
	int i = 0;
	for (i = 0; string[i]!=0 && flag; i++){
		if(string[i]==' '){
			string[i]=0;
			flag = 0;
		}
	}
	postBuffer = string + i;
}

void ceroDivision(){
	ceroDiv();
}

void invalidOperation(){
	invalidOpCode();
}

void clearBufferTerminal(){
	for (int i = 0; i < TERMINALDIM; i++){
		bufferTerminal[i] = 0;
		postBuffer = bufferTerminal;
	}
	longitud = 0;
}