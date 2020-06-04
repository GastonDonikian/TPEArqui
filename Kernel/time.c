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

void timeGetter(char * results) {
	char secs, mins, hours;
	hours = hoursRTC();
	mins = minutesRTC();
	secs = secondsRTC();
	int i = 0;
	results[i++] = ((hours >> 4) + '0');
	results[i++] = ((hours & 0x0F) +'0');
	results[i++] = (':');
	results[i++] = ((mins >> 4) +'0');
	results[i++] = ((mins & 0x0F) + '0');
	results[i++] = (':');
	results[i++] = ((secs >> 4) + '0');
	results[i] = ((secs & 0x0F) + '0');	
}