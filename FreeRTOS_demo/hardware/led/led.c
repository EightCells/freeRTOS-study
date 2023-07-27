#include <gd32f30x.h>
#include "led.h"

void led_init(void)
{
	/* PD01 remapping */
	rcu_periph_clock_enable(RCU_AF); 
	gpio_pin_remap_config(GPIO_PD01_REMAP, ENABLE);
	
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOD);
	
    /* configure led GPIO port */ 
    gpio_init(GPIOD, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_0);
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);

    GPIO_BC(GPIOD) = GPIO_PIN_0;
	GPIO_BC(GPIOC) = GPIO_PIN_15;
}

void led_switch(int state)
{   
    if (state == LED_ON)
    {
		gpio_bit_set(GPIOC, GPIO_PIN_15);
    }
    else if (state == LED_OFF)
    {
        gpio_bit_reset(GPIOC, GPIO_PIN_15);
    }
}
