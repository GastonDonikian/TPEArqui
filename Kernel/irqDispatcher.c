#include <stdint.h>
#include "time.h"
#include "keyboard.h"

void int_20();
void int_21(uint64_t rsp);
void irqDispatcher(uint64_t irq,uint64_t rsp) {
	switch (irq) { //CAMIAR POR UN ARREGLO DE PUNTEROS AA FUNCION!!!!!
		case 0:
			int_20();
			break;
		case 1:
			int_21(rsp);
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

void int_21(uint64_t rsp){
	keyboard_handler(rsp);
}