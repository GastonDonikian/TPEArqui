/* sampleCodeModule.c */
#include <stdint.h>
void read(char * buf, uint64_t count);
void write(char * buf, uint64_t count, uint64_t abajoarriba);

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	char hola[]="Hola mundo";
	write(hola, 10, 0);
	putChar('m');
	putChar('b');
	putChar('e');
	putChar('h');
	char a ='e';
	putChar(a);
	a=getChar();
	putChar(a);
	a=getChar();
	putChar(a);
	while(1) {
		putChar(getChar());
	}
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}