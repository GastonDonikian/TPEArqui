#include <stdint.h>
#include "video_driver.h"
#include "screenManager.h"
#define WIDTH 1024
#define HEIGHT 768
#define MULT 2
#define CHAR_SIZE MULT*8
#define LINE HEIGHT/(CHAR_SIZE)
#define CHARACTERS WIDTH/(CHAR_SIZE*SCREENS)
#define SCREENS 2
#define SCREEN_WIDTH WIDTH/SCREENS

unsigned char posScreen[SCREENS] = {0};
unsigned char lineScreen[SCREENS] = {0}; 
unsigned char select = 0;

void cleanLine(unsigned char line);

void printChar(unsigned char ascii) { //imprime un caracter
	printCharByPixel(posScreen[select]*CHAR_SIZE + SCREEN_WIDTH *select,lineScreen[select]*CHAR_SIZE,ascii);
	posScreen[select]++;
	if(posScreen[select] >= CHARACTERS) {
		newLine();
	}
}

void printCharAt(unsigned char ascii, unsigned char line) { //imprime un caracter en la linea especificada
	if(line <= 0)
		return;
	if(line != lineScreen[select]) {
		cleanLine(line);
		posScreen[select] = 0;
		lineScreen[select] = line;
	}
	printChar(ascii);
}

void printLineAt(char * string, unsigned char line) { //imprime una linea en la linea especificada
	printAt(string,line);
	newLine();
}

void printAt(char * string, unsigned char line) { //IMPRIME UN STRING DE CARACTERES EN LA LINEA DADA, NO IMPRIME UNA LINEA
	if(line <= 0)
		return;
	if(line != lineScreen[select]) {
		cleanLine(line);
		posScreen[select] = 0;
		lineScreen[select] = line;
	}
	print(string);
}

void cleanLine(unsigned char line) { //BORRA LA LINEA DE LA PANTALLA SELECCIONADA
	for(int i = 0; i < SCREEN_WIDTH;i++) {
		for(int j = 0; j < CHAR_SIZE; j++) {
			writeScreen(i + SCREEN_WIDTH*select,j + line*CHAR_SIZE);
		}
	}
}

void selector(unsigned char screen) { //CAMBIA EL SELECT Y INICIALIZA LA PRIMER LINEA
	select = screen;
	initializeScreen();
}

void initializeScreen() {//HIGHLITEA LA PANTALLA EN LA QUE ESTAS CUANDO CAMBIAS DE PANTALLA	
	if(select >= SCREENS || select < 0)
		return;
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < CHAR_SIZE;j++) {
			if(select == 0) {
				if(i < SCREEN_WIDTH) 
					writePixel(i,j);
				else 
					writeScreen(i,j);
			}
			else { //LOGICA HORRIBLE PORQUE NO PUDIMOS HACERLO MEJOR
				if(i > SCREEN_WIDTH) 
					writePixel(i,j);
				else 
					writeScreen(i,j);
			}
		}
	}
	ignoreFirstLine();
}


void ignoreFirstLine() { //IGNORA LA PRIMER LINEA PARA QUE NO ME ESCRIBA DONDE ESTA SELECCIONADO
	for(int i = 0; i < SCREENS; i++)
		if(lineScreen[i] == 0)
			lineScreen[i] = 1;	
}

void changeScreen(void) { //ALTERNA DE PANTALLA
	if(select == SCREENS - 1)
		selector(0);
	else
		selector(select+1);
}

void printLine(char * string) { //IMPRIME UNA LINEA SIGUIENDO EL ORDEN NATURAL
	print(string);
	newLine();
}
void print(char * string) { //IMPRIME EL ORDEN NATURAL SIN HACER UNA LINEA
	int i = 0;
	while(string[i] != 0)
	printChar(string[i++]);
}

void clearScreen() { //LIMPIA LA PANTALLA ACTUAL
	for(int i = 0; i < HEIGHT;i++)
		for(int j = 0; j < SCREEN_WIDTH;j++){
			writeScreen(j + SCREEN_WIDTH*select ,i);
	}	
}

void newLine(void) { //IMPRIME UNA LINEA /n
	if(lineScreen[select] == LINE-1) {
		clearScreen();
		lineScreen[select] = 0;
		posScreen[select] = 0;
	}
	lineScreen[select]++;
	posScreen[select] = 0;
}

//void scrollUp();
//void scrollDown();