#include <gd32f30x.h>

// timer
void TIM4_Init(uint32_t arr,uint32_t psc)
{
	timer_parameter_struct timer_init_struct;
	
	rcu_periph_clock_enable(RCU_TIMER4);
	
	timer_deinit(TIMER4);
	timer_init_struct.prescaler = psc;
	timer_init_struct.period = arr;
	timer_init_struct.alignedmode = TIMER_COUNTER_EDGE;
	timer_init_struct.counterdirection = TIMER_COUNTER_UP;
	timer_init_struct.clockdivision = TIMER_CKDIV_DIV1;
	timer_init_struct.repetitioncounter = 0;
	timer_init(TIMER4, &timer_init_struct);
	
	nvic_irq_enable(TIMER4_IRQn, 1, 1);
	timer_interrupt_enable(TIMER4, TIMER_INT_UP);
	
	timer_enable(TIMER4);
}

unsigned long sys_time = 0;
void TIMER4_IRQHandler(void)
{
	if (timer_interrupt_flag_get(TIMER4, TIMER_INT_FLAG_UP))
	{
		++sys_time;
	}
	
	timer_interrupt_flag_clear(TIMER4, TIMER_INT_FLAG_UP);
}
