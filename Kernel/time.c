#include <time.h>
#include <naiveConsole.h>
static unsigned long ticks = 0;
char secondsRTC();
char minutesRTC();
char hoursRTC();


void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void timeGetter(int * results) {
	results[0] = hoursRTC();
	results[1] = minutesRTC();  
	results[2] = secondsRTC();	
}
