#include <keyboard.h>
#include <stdint.h>
#include <lib.h>
#include "screenManager.h"
#include "programManager.h"
#define BUFFERSIZE 10
extern char keyPressed();
extern char getKey();

unsigned char asccode[58][2] ={ {0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
 {'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
 {'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
 {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},
 {'/','?'},{0,0},{0,0},{0,0},{' ',' '}};

int buffer_position = 0;
char keyboardBuffer[BUFFERSIZE]={0};
unsigned int reading_position= 0;
char shift = 0;

char wasKeyPressed(){
	return keyPressed();
}

void keyboard_handler(uint64_t rsp){
	unsigned int scancode =0;
	unsigned char keyPress;
	if(wasKeyPressed()){
		scancode = getKey();
		if(scancode == 54){
			shift =1;
		}
		else if (scancode == 182){
			shift = 0;
		}
		else if(scancode == 1) {
			currentRegisters(rsp);
		}
		else if(scancode == 56){
			switchFun(rsp);
		}
		else if(scancode <58){
			keyPress = asccode[scancode][shift];
			addToBuffer(keyPress);
		}

	}
}
void addToBuffer(char key){
	if (buffer_position < BUFFERSIZE){
		keyboardBuffer[buffer_position++] = key;
	}
	else {
		buffer_position=0;
		keyboardBuffer[buffer_position++]= key;
	}
}

void keyboard_reader(char * result){
	if (reading_position>=BUFFERSIZE)
	{
		reading_position=0;
	}
	*result=keyboardBuffer[reading_position];

	if(keyboardBuffer[reading_position]!=0){
		keyboardBuffer[reading_position++]=0;
	}

}