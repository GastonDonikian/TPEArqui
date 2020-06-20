#ifndef _videoDriver_
#define _videoDriver_
void writePixel(int x, int y);
void writeScreen(int x, int y);
void printCharByPixel(int x, int y,unsigned char ascii);
void printAnyCharByPixel(int x, int y, unsigned char ascii,unsigned char red, unsigned char green, unsigned char blue);
char isItWriten(int x, int y);
void clear(void);

#define WIDTH 1024 
#define HEIGHT 768
#define MULT 2
#define CHAR_SIZE MULT*8
#define LINE HEIGHT/(CHAR_SIZE)
#define CHARACTERS WIDTH/(CHAR_SIZE*SCREENS)
#define SCREENS 2
#define SCREEN_WIDTH WIDTH/SCREENS
/*void printLineByPixel(int x, int y, char * string);
void printChar(char ascii);
void printLine(char * string);
void clear(void);
void newLine(void);
*/
#endif