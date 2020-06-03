#include <stdint.h>
extern void read(char * buf);
extern void write(char * buf, uint64_t count, uint64_t abajoarriba);
char getChar(){
	char a=0;
	while(a==0){
		read(&a);
	}
	return a;
}

void putChar(char a){
	write(&a, 1, 0);
	return;
}
