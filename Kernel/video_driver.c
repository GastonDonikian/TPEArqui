#include <stdint.h>
#include "video_driver.h"
#include "fonts.h"
#define WIDTH 1024
#define HEIGHT 768
#define MULT 2
#define LINE HEIGHT/(MULT*8)
#define CHARACTERS WIDTH/(MULT*8)
struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));


struct vbe_mode_info_structure * screen_info = 0x5C00;
unsigned char mask[] = {128,64,32,16,8,4,2,1};

int pos = 0; //Caracter de la pantalla
int line = 0; //linea en la pantalla
char * getPixelDataByPosition(int x, int y) {
	return (screen_info->framebuffer + 3 * (x + y * WIDTH));
}

char isItWriten(int x, int y) {
	if(getPixelDataByPosition(x,y)[0] != 0)
		return 1;
	return 0;
}

void writePixel(int x, int y) { //x es el width, y es el height
	char * pos = getPixelDataByPosition(x,y); // &(screen_info).framebuffer
	pos[0] = 255;//AZUL
	pos[1] = 255;//VERDE
	pos[2] = 255; //ROJO
}
void writeScreen(int x, int y) {
	char * pos = getPixelDataByPosition(x,y); // &(screen_info).framebuffer
	pos[0] = 0;//AZUL
	pos[1] = 0;//VERDE
	pos[2] = 0; //ROJO
}

void writeAnyPixel(int x, int y,unsigned char red,unsigned char green,unsigned char blue) {
	char * pos = getPixelDataByPosition(x,y);
	pos[0] = blue;
	pos[1] = green;
	pos[2] = red;
}

void clear(void){
	for(int i = 0; i < HEIGHT;i++)
		for(int j = 0; j < WIDTH;j++){
			writeScreen(j,i);
		}	
}

void printCharByPixel(int x, int y,unsigned char ascii) { //PASAR DE MOVERSE POR PIXELES A MOVERSE POR LINEAS Y CARACTERES
	for(int i = 0; i < 8*MULT; i++)
		for(int j = 0; j < 8*MULT;j++) {
			if((font8x8_basic[ascii][i/MULT] & mask[7-j/MULT]) != 0){ // EL HOMBRE QUE ARMO EL FONT HIZO TODO AL REVEZ!!!     0000000
				writePixel(x+j,y+i);
			}else
				writeScreen(x+j,y+i); //CON EL J++ ME QUEDA EN MULT
		}
}

void printAnyCharByPixel(int x, int y, unsigned char ascii,unsigned char red, unsigned char green, unsigned char blue) {
	for(int i = 0; i < 8*MULT; i++)
		for(int j = 0; j < 8*MULT;j++) {
			if((font8x8_basic[ascii][i/MULT] & mask[7-j/MULT]) != 0){ 
				writeAnyPixel(x+j,y+i,red,green,blue);
			}else
				writeScreen(x+j,y+i); 
		}
}