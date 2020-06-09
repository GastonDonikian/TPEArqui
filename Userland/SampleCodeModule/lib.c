#include <stdint.h>
#include <stdarg.h>
#include "lib.h"
#define EPSILON 0.0001
extern void read(char * buf);
extern void write(char * buf, uint64_t count, uint64_t abajoarriba);
extern void switchScreen();
extern void time(char * buf);
extern void getCpuid(char * buf);
extern void	cputemp(char * buf);
extern void addProgram(void * func);
extern void startRunning();


char screenPrint[2] = {0};
int screen = 0;

void getCpuTemp(char * answer){
	cputemp(answer);
}

void getCpu(char * answer){
	getCpuid(answer);
}
int stringToInt(char * string){
	int resp=0;
	int pow=1;
	for (int i = 0; string[i]!=0 ; i++){
		pow*=10;
	}
	pow/=10;
	for (int i = 0; string[i]!=0; i++){
		resp += (string[i]-'0')*pow;
		pow/=10;
	}
	return resp;
}
void intToString(int num, char * result){
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

void timeGetter(char * buff){
	time(buff);
}

char getChar(){
	char a=0;
	while(a==0){ //NO SERIA MEJOR TENER UN BUFFER Y QUE UNA VEZ QUE ES DISTINTO DE CERO LEA HASTA QUE VUELVA A SER CERO? no para el getChar pero para scanf
		read(&a);
	}
	return a;
}

void putChar(char a){
	write(&a, 1, screenPrint[screen]);
	return;
}

void printf(char * string) {
	int i = 0;
	while(string[i++] !=0);
	write(string,i - 1,screenPrint[screen]);
}
/*void printf(char *fmt,...){ //FUNCION SACADA DE "THE C PROGRAMMING LANGUAJE" - Brian W. Kernighan Dennis M. Ritchie
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	va_start(ap,fmt);
	for(p = fmt; *p;p++) {
		if(*p != '%') {
			putChar(*p);
			continue;
		}
		switch(*++p) {
			case 'd':
				ival = va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				dval = va_arg(ap,double);
				printf("%f",dval);
				break;
			case 's':
				for(sval = va_arg(ap,char *);*sval;sval++)
					putChar(*sval);
				break;
			default:
				putChar(*p);
				break;
		}
	}
	va_end(ap);
}*/

void changeScreen() {
	switchScreen();
	if(screen == 1)
		screen = 0;
	else
		screen =  1;
}

void setUpDown(int i) {
	screenPrint[screen]=i;
}

int stringCmp(char * string1, char * string2){
	int flag =1;
	for (int i = 0;(string1[i]!=0 || string2[i]!=0) && flag; i++){
		if (string1[i] != string2[i]){
			flag =0;
		}
	}
	return flag;
}

int isItANumber(char ch) { //DICE SI ES UN NUMERO
	return (ch >= '0' && ch <= '9');
}

double stringToDouble(char * string) {
	double rta = 0;
	int pointPosition = 0;
	int length = 0;
	double pow = 0.1;
	while(*string == '0')
		string = string+1;
	while(isItANumber(string[length]) || string[length] == '.') { //CAMBIAR != 0 POR PARENTESIS O OPERANDO Y VALIDAR!
		if(string[length] == '.') {
			if(pointPosition)
				return 0; //HUBO UN ERROR!
			pointPosition = length;
		}
		if(!pointPosition)
			pow = pow*10;
		length++;
	}
	for(int i = 0; i < length;i++) {
		if(i != pointPosition || (pointPosition == 0)){
			rta = rta +  (string[i] - '0') * pow;
			pow = pow/10;
		}
		 	
	}
	return rta;
}

void doubleToString(double doub,char * string) {
	int casteo = (int)doub;

	if(doub < 0) {
		string[0] = '-';
		doub = doub*(-1);
		doubleToString(doub,string+1);
		return;
	}

	if(casteo == 0) {
		string[0] = '0';
	}
	else	
		intToString(casteo,string);
	
	doub = doub - casteo; //0, ALGO	
	
	int length = 0;
	if(casteo == 0)
		length = 1;
	while(casteo != 0) {
		casteo = casteo/10;
		length++;
	}
	if(doub >EPSILON) {
		string[length] = '.';
		for(int i = 1; i <= 4; i++) {
			doub = doub * 10;
			casteo = (int)(doub);
			string[length + i] = casteo + '0';
			doub = doub - casteo;
		}
		string[length + 5] = 0;
		return;
	}
	string[length] = 0;

}

void charToBits(char ch, char * string) {
	int j = 1;
	for(int i = 7; i >= 0; i--) {
		string[i] =((ch & j)>>(7-i)) +'0';
		j = j*2;
	}
	string[8] = 0;
}

void printAllRegisters(long int * registerArray) { //SABEMOS QUE ACA ESTAN REPETIDAS PERO UNA ES LIB DE KERNEL Y OTRA DE USERLAND
	char * registerNamesArray[] = {"r15","r14","r13","r12","r11","r10","r9","r8","rsi",
	"rdi","rbp","rdx","rcx","rbx","rax","rip"};
	for(int i = 0; i < 15 ;i++ ) {
		printf(registerNamesArray[i]);
		if(i == 6 || i == 7)
			putChar(' ');
		putChar(' ');
		printRegister(registerArray[i]);
		putChar('\n');
	}
}
void printRegister(long int reg) {
	char array[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char aux;
	for(int i = 0; i < 16;i++) { 
		aux = (reg & 0xF000000000000000) >> 60; 
		reg = reg << 4;
		putChar(array[aux]);
	}
	putChar('h');
	return;
}


void add_program(void * function){
	addProgram(function);
}

void start(){
	startRunning();
}