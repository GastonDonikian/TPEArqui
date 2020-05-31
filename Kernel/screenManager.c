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


void printChar(unsigned char ascii) {
	printCharByPixel(posScreen[select]*(MULT*8) + SCREEN_WIDTH *select,lineScreen[select]*(MULT*8),ascii);
	posScreen[select]++;
	if(posScreen[select] >= CHARACTERS) {
		newLine();
	}
}

void selector(unsigned char screen) {
	select = screen;
	initializeScreen();
}

void initializeScreen() {
	ignoreFirstLine();	
	if(select >= SCREENS || select < 0)
		return;
	for(int i = 0; i < WIDTH; i++) {
		int current = i/SCREEN_WIDTH;
		if(current == select) {
			for(int j = 0; j < CHAR_SIZE;j++)
				writePixel(i,j);
		}
		else {
			for(int  j = 0; j < CHAR_SIZE;j++)
				writeScreen(i,j);
		}
	}
}

void ignoreFirstLine() { 
	for(int i = 0; i < SCREENS; i++)
		if(lineScreen[i] == 0)
			lineScreen[i] = 1;	
}

void changeScreen(void) {
	if(select == SCREENS - 1)
		selector(0);
	else
		selector(select+1);
}

void printLine(char * string) {
	int i = 0;
	while(string[i] != 0)
		printChar(string[i++]);
	newLine();
}
void clearScreen() {
	for(int i = 0; i < HEIGHT;i++)
		for(int j = 0; j < SCREEN_WIDTH;j++){
			writeScreen(j + SCREEN_WIDTH*select ,i);
	}	
}
void newLine(void) { 
	if(lineScreen[select] == LINE-1) {
		clearScreen();
		lineScreen[select] = 0;
		posScreen[select] = 0;
	}
	lineScreen[select]++;
	posScreen[select] = 0;
}