#include <stdint.h>
#include "video_driver.h"
#include "screenManager.h"



void initializeScreen(unsigned char select) {//HIGHLITEA LA PANTALLA EN LA QUE ESTAS CUANDO CAMBIAS DE PANTALLA	
	if(select >= SCREENS)
		return;
	for(int  i = 0; i < HEIGHT;i++){
		writeAnyPixel(SCREEN_WIDTH+1, i,0,128,255);
		writeAnyPixel(SCREEN_WIDTH, i,0,128,255);
	}
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < CHAR_SIZE;j++) {
			if(select == 0) {
				if(i < SCREEN_WIDTH) 
					writePixel(i,j);
				else 
					writeScreen(i,j);
			}
			else { //LOGICA HORRIBLE PORQUE NO PUDIMOS HACERLO MEJOR
				if(i > SCREEN_WIDTH) 
					writePixel(i,j);
				else 
					writeScreen(i,j);
			}
		}
	}
}
void clearScreen(unsigned char select) { //LIMPIA LA PANTALLA ACTUAL
	for(int i = CHAR_SIZE; i < HEIGHT;i++)
		for(int j = 0; j < SCREEN_WIDTH;j++){
			writeScreen(j + (SCREEN_WIDTH+2)*select ,i);
	}	
}




