#ifndef _videoDriver_
#define _videoDriver_
void writePixel(int x, int y);
void writeScreen(int x, int y);
void printCharByPixel(int x, int y,unsigned char ascii);
char isItWriten(int x, int y);
/*void printLineByPixel(int x, int y, char * string);
void printChar(char ascii);
void printLine(char * string);
void clear(void);
void newLine(void);
*/
#endif