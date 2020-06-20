#ifndef _terminal_
#define _terminal_

void gotoFunction(int number, char * postBuffer);
void analize(char * buffer);
void terminal();
void help();
void inforeg();
void printmem(char * pointString);
void gettime();
void getid();
void cpuTemperature();
void cleanString(char * string);
void removePreSpaces(char * string);
void removePostSpaces(char * string);
void clearBufferTerminal();
void ceriDivision();
void invalidOperation();

#endif