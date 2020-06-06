#include <stdint.h>
#include <stdarg.h>
#define EPSILON 0.0001
extern void read(char * buf);
extern void write(char * buf, uint64_t count, uint64_t abajoarriba);
extern void switchScreen();
extern void time(char * buf);


char screenPrint[2] = {0};
char screen = 0;

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



double stringToDouble(char * string) {
	double rta = 0;
	int pointPosition = 0;
	int length = 0;
	double pow = 0.1;
	while(*string == '0')
		string = string+1;
	while(isANumber(string[length]) || string[length] == '.') { //CAMBIAR != 0 POR PARENTESIS O OPERANDO Y VALIDAR!
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
	if(casteo ==0) {
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