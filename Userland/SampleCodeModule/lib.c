#include <stdint.h>
extern void read(char * buf);
extern void write(char * buf, uint64_t count, uint64_t abajoarriba);
extern void switchScreen();


char screenPrint[2] = {0};
char screen = 0;
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

void printf(char * string){
	int i = 0;
	while(string[i++] != 0);
	write(string,i-1,screenPrint[screen]);
}

void changeScreen() {
	switchScreen();
	if(screen == 1)
		screen = 0;
	else
		screen =  1;
}

void changeUpDown() {
	if(screenPrint[screen])
		screenPrint[screen]--;
	else
		screenPrint[screen]++;
}
