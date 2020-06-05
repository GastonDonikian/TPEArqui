#include <stdint.h>
#include <stdarg.h>

extern void read(char * buf);
extern void write(char * buf, uint64_t count, uint64_t abajoarriba);
extern void switchScreen();
extern void time(char * buf);


char screenPrint[2] = {0};
char screen = 0;

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
			return;
		}
	}
}