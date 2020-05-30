#include <time.h>
#include <naiveConsole.h>
static unsigned long ticks = 0;
char secondsRTC();
char minutesRTC();
char hoursRTC();


void timer_handler() {
	ticks++;
//	writeHour(); 
	if(ticks%(18*5) ==0)
		ncPrint("Pasaron 5 segundos!");
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void writeHour(void) { 
	char * buffer = 0xB8000; //IMPRIME LA HORA SIEMPRE AL PRINCIPIO DE LA PANTALLA
	char hour,min,secs;
	hour = hoursRTC();
	min = minutesRTC();  
	secs = secondsRTC();
	buffer[0]=(hour>>4)+'0';
	buffer[2]=(hour & 0x0F)+'0';
	buffer[4]=':';
	buffer[6]=(min>>4)+'0';
	buffer[8]=(min & 0x0F)+'0';
	buffer[10]=':';
	buffer[12]=(secs>>4)+'0';
	buffer[14]=(secs & 0x0F)+'0';
	buffer[16] = 0x0;
}
