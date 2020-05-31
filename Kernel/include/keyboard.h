#include <stdint.h>
#ifndef _keyboard_
#define _keyboard_ 
char wasKeyPressed();
void keyboard_handler();
void addToBuffer(char key);
void keyboard_reader(char * result, int count);
#endif