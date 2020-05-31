#ifndef _screenManager_
#define _screenManager_

void printChar(unsigned char ascii);
void selector(unsigned char screen);
void initializeScreen();
void changeScreen(void);
void printLine(char * string);
void clearScreen();
void newLine(void);
void printCharAt(unsigned char ascii, unsigned char line);
void print(char * string)
void printAt(char * string, unsigned char line) ;
void printLineAt(char * string, unsigned char line);

#endif