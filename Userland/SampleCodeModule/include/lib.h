#ifndef _stdLib_
#define _stdLib_ 
char getChar();
void timeGetter(char * buff);
void putChar(char a);
void printf(char * string);
void changeScreen();
void setUpDown(int i);
void removePreSpaces(char * string);
void removePostSpaces(char * string);
void cleanString(char * string);
double stringToDouble(char * string);
void doubleToString(double doub);
#endif