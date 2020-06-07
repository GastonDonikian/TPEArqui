#include <stdint.h>
#ifndef _keyboard_
#define _keyboard_ 
char wasKeyPressed();
void keyboard_handler(uint64_t rsp);
void addToBuffer(char key);
void keyboard_reader(char * result);
#endif