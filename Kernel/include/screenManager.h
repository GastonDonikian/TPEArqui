#ifndef _screenManager_
#define _screenManager_

void printChar(unsigned char ascii);
void selector(unsigned char screen);
void initializeScreen();
void changeScreen(void);
void printLine(char * string);
void clearScreen();
void newLine(void);

#endif