#ifndef _irq_dispatcher_
#define _irq_dispatcher_ 
void int_20();
void int_21(uint64_t rsp);
void irqDispatcher(uint64_t irq,uint64_t rsp);
#endif	