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
void add_program(void * func);
void start();
void printRegister(long int reg);
void printAllRegisters(long int * registerArray);
int stringCmp(char * string1, char * string2);
int stringToInt(char * string);
int isItANumber(char ch);
#endif