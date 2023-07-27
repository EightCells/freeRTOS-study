#include "FreeRTOS.h"
#include "led.h"
#include "task.h"

static void system_init(void);

//task handles
static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LEDTask_Handle = NULL;

//task create functions
static BaseType_t create_led_task(void);

//task functions
static void AppTaskCreate(void);
static void led_task(void);

int main()
{
    BaseType_t xReturn = pdPASS;
    
    system_init();
    
    xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,            //任务函数
                          (const char*)"AppTaskCreate",         //任务名
                          (uint16_t)512,                            //栈大小
                          (void*)NULL,                              //参数
                          (UBaseType_t)1,                           //优先级
                          (TaskHandle_t*)&AppTaskCreate_Handle);    //TCB引用
    if (xReturn == pdPASS)
    {
        vTaskStartScheduler();  //开始任务调度
    }
    else
        return -1;
    
    while (1);
}

void system_init(void)
{
    led_init();
}

BaseType_t create_led_task(void)
{
    BaseType_t xReturn = pdPASS;
    taskENTER_CRITICAL();
    xReturn = xTaskCreate((TaskFunction_t)led_task,
                          (const char*)"LED_task",
                          (uint16_t)512,
                          (void*)NULL,
                          (UBaseType_t)2,
                          (TaskHandle_t*)&LEDTask_Handle);
    taskEXIT_CRITICAL();
    return xReturn;
}

void AppTaskCreate(void)
{
    while (create_led_task() != pdPASS) vTaskDelay(50);
    vTaskDelete(AppTaskCreate_Handle);
}

void led_task(void)
{
    while (1)
    {
        led_switch(LED_ON);
        vTaskDelay(500);
        led_switch(LED_OFF);
        vTaskDelay(500);
    }
}


