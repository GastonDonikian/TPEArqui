#include <keyboard.h>

extern char keyPressed();
extern char getKey();

static char asccode[58][2] ={ {0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
 {'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
 {'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
 {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},
 {'/','?'},{0,0},{0,0},{0,0},{' ',' '}};


char wasKeyPressed(){
	return keyPressed();
}

void keyboard_handler(){
	static char shift;
	unsigned char scancode =250;
	unsigned char keyPress;
	if(wasKeyPressed()){
		scancode = getKey();
		if(scancode == 54){
			shift =1;
		}
		else if (scancode == 182){
			shift = 0;
		}
		else if(scancode <128){
			keyPress = asccode[scancode][shift];
			printChar(keyPress);
		}
	}
}