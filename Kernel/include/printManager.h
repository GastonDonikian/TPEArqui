#ifndef _printManager_
#define _printManager_
void copyLine(unsigned char source, unsigned char destiny);
void newLine();
void cleanLine(unsigned char line);
void printLine(char * string);
void print(char * string);
void printChar(unsigned char ascii);
void selector();
void screenWriter(char * buffer, uint64_t count, uint64_t upordown);
void deleteChar();
#endif