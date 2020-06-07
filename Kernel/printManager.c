#include <stdint.h>
#include "video_driver.h"
#include "printManager.h"
#define WIDTH 1024 
#define HEIGHT 768
#define MULT 2
#define CHAR_SIZE MULT*8
#define LINE HEIGHT/(CHAR_SIZE)
#define CHARACTERS WIDTH/(CHAR_SIZE*SCREENS)
#define SCREENS 2
#define SCREEN_WIDTH WIDTH/SCREENS

unsigned char posScreen[SCREENS] = {0};
unsigned char lineScreen[SCREENS] = {1,1}; 
unsigned char select = 0;
unsigned char upDown = 0;

void screenWriter(char * buffer, uint64_t count, uint64_t upordown){
	upDown = upordown;
	for (int i = 0; i < count; i++){
		if(buffer[i]=='\n'){
			newLine();
		}
		else if(buffer[i]=='\t'){
			print("        "); //SILICON VALLEY DICTA QUE SON 8 SPACES
		}
		else if(buffer[i]=='\b'){
			deleteChar();
		}
		else{
			printChar(buffer[i]);
		}
	}
}

void selector() {
	if(select)
		select--;
	else
		select++;
	initializeScreen(select);
	//upDown = 1; ESTO NO SE PORQUE ESTA ACA
}
void printAnyChar(unsigned char ascii,unsigned char red,unsigned char green,unsigned char blue) {
	if(upDown == 1) {
		lineScreen[select] = LINE -1;
	}	
	if(posScreen[select] >= CHARACTERS) {
		newLine();
	}
	printAnyCharByPixel(posScreen[select]*CHAR_SIZE + SCREEN_WIDTH*select,lineScreen[select]*CHAR_SIZE,ascii,red,green,blue);
	posScreen[select]++;
}

void printChar(unsigned char ascii){ //UPDEATEADO UPDOWN
	printAnyChar(ascii,255,255,255);
}

void print(char * string) { //UPDATEADO UPDOWN
	int i = 0;
	while(string[i] != 0) {
		printChar(string[i++]);
	}
}

void printLine(char * string) {
	print(string);
	newLine();
}

void cleanLine(unsigned char line){ //BORRA LA LINEA DE LA PANTALLA SELECCIONADA
	for(int i = 0; i < SCREEN_WIDTH;i++) {
		for(int j = 0; j < CHAR_SIZE; j++) {
			writeScreen(i + SCREEN_WIDTH*select,j + line*CHAR_SIZE);
		}
	}
}

void newLine() { //UPDATEADO UPDOWN
	if(upDown) {
		for(int i = 2; i < LINE;i++) {
			copyLine(i,i-1); //COPIO LA LINEA I EN LA LINEA I -1
		}
		cleanLine(LINE - 1);
		posScreen[select] = 0;
	}
	else {
		if(lineScreen[select] == LINE-1) {
			clearScreen(select);
			lineScreen[select] = 0;
		}
		lineScreen[select]++;
		posScreen[select] = 0;
	}
}

void copyLine(unsigned char source, unsigned char destiny) {
	cleanLine(destiny);
	for(int i = 0; i < SCREEN_WIDTH;i++) 
		for(int j = 0; j < CHAR_SIZE; j++) 
			if(isItWriten(i + select*SCREEN_WIDTH,j+source*CHAR_SIZE))
				writePixel(i + select*SCREEN_WIDTH,j+destiny*CHAR_SIZE);
}

void deleteChar() {
	
	if(upDown) {
		if(posScreen[select] > 0) {
			posScreen[select]--;
			printChar(0);
			posScreen[select]--;
		}
		else {
			scrollDown(); //APARENTEMENTE SOLO SE PUEDE BORRAR LA ULTIMA LINEA
			posScreen[select] = CHARACTERS;
		}
	}
	else{
		if(posScreen[select] == 0 && lineScreen[select] == 1)
			return;
		else if(posScreen[select] == 0) {
			lineScreen[select]--;
			posScreen[select] = CHARACTERS ;
		}
		posScreen[select]--;
		printChar(0);
		posScreen[select]--;
	}
	
}

void scrollDown() {
	for(int i = LINE -2; i > 0; i--) {
		copyLine(i,i+1);
	}
}

void cleanScreen() {
	clearScreen(select);
	posScreen[select] = 0;
	lineScreen[select] = 1;
}
