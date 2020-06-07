#ifndef _stdLib_
#define _stdLib_ 
char getChar();
void timeGetter(char * buff);
void putChar(char a);
void printf(char * string);
void changeScreen();
void setUpDown(int i);
double stringToDouble(char * string);
void doubleToString(double doub,char * string);
void getCpu(char * answer);
void getCpuTemp(char * answer);
void charToBits(char ch, char * string);
void intToString(int num, char * result);
#endif