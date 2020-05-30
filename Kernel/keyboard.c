#include <keyboard.h>

char keyPressed();
char getKey();

char map[] = {0,0,'1','2','3','4','5','6','7','8','9','0',0,0,0,0,'q','w','e','r',
't','y','u','i','o','p',0,0,0,0,'a','s','d','f','g','h','j','k','l','ñ',0,0,0,0,'z','x','c','v','b','n','m',',','.'};

char wasKeyPressed(){
	return keyPressed();
}

char getKeyPressed() {
	if(wasKeyPressed()) {
		unsigned char c = getKey();
		if(c > 52)
			return 0;
		ncPrintChar(map[c]);
	}
	return 0;
}
