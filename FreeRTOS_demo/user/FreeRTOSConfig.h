#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 * 可以在下面这个网站查看对应选项的官方解释，此文件的注释只做参考
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
//#include "gd32f30x.h"
/* 这个是踩过的坑，因为汇编也要用到FreeRTOSConfig.h文件，所以有些关键字
 * 如 enum 就会报 bad instruction 的错误，所以最好还是直接把如 
 * SystemCoreClock 这样的宏的值直接粘贴过来用，像我下面那样，就不要再包含
 *  gd32f30x.h 了。*/
/* Ensure stdint is only used by the compiler, and not the assembler. */
//这个地方__ICCARM__表示是IAR的编译器，若是Keil或GCC要改成__CC_ARM、__GNUC__
#if defined __ICCARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

//assert断言
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	

/*****************************************************************************
 *                                基础配置项
 ****************************************************************************/
//调度器：抢占式 1 协作式 0
#define configUSE_PREEMPTION			1

//1 使能时间片调度(默认是使能的)
#define configUSE_TIME_SLICING          1

//是否使用硬件计算前导0的方式选择下一个可执行任务
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* 置1：使能低功耗tickless 模式；置0：保持系统节拍（tick）中断一直运行 */
#define configUSE_TICKLESS_IDLE         0

//写入实际CPU内核时钟频率
#define configCPU_CLOCK_HZ				((uint32_t)(120000000))//( SystemCoreClock )

//1s中断的次数
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )

//可用的最大优先级
#define configMAX_PRIORITIES			( 32 )

//空闲任务堆栈大小
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )

//任务名称最大长度
#define configMAX_TASK_NAME_LEN			( 16 )

//系统节拍计数器变量的数据类型，1 16位无符号整数，0 32位无符号整数
#define configUSE_16_BIT_TICKS			0

//空闲任务放弃CPU使用权给其他同级任务（建议所有其他任务的优先级高于空闲任务）
#define configIDLE_SHOULD_YIELD			1

//启用队列
#define configUSE_QUEUE_SETS            1

//开启任务通知功能，默认开启
#define configUSE_TASK_NOTIFICATIONS    1

//互斥信号量
#define configUSE_MUTEXES               1

//可以注册的信号量的个数
#define configQUEUE_REGISTRY_SIZE       10

//使用递归互斥信号量
#define configUSE_RECURSIVE_MUTEXES     1

//可注册的消息队列的个数
#define configUSE_APPLICATION_TASK_TAG  0

//使用计数信号量
#define configUSE_COUNTING_SEMAPHORES   1

/*****************************************************************************
 *                                内存申请相关
 ****************************************************************************/
//支持动态内存申请
#define configSUPPORT_DYNAMIC_ALLOCATION 1
//支持静态内存
#define configSUPPORT_STATIC_ALLOCATION 0
//总堆栈大小
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 36 * 1024 ) )

/*****************************************************************************
 *                                钩子函数相关
 ****************************************************************************/
//空闲钩子（空闲任务执行的应用程序函数，void vApplicationIdleHook( void );
#define configUSE_IDLE_HOOK				0
//时间片钩子函数 void vApplicationTickHook( void );
#define configUSE_TICK_HOOK				0
//malloc失败时（返回NULL）调用的钩子函数 void vApplicationMallocFailedHook( void );
#define configUSE_MALLOC_FAILED_HOOK    0
//堆栈溢出检测 大于0时启用，必须由用户提供堆栈溢出钩子函数
#define configCHECK_FOR_STACK_OVERFLOW  0

/*****************************************************************************
 *                         运行时间和任务状态收集相关
 ****************************************************************************/
//启用运行时间统计功能
#define configGENERATE_RUN_TIME_STATS   0
//启用可视化跟踪调试
#define configUSE_TRACE_FACILITY        0
/* 与宏configUSE_TRACE_FACILITY 同时为 1 时会编译下面 3 个函数
 * prvWriteNameToBuffer()
 * vTaskList(),
 * vTaskGetRunTimeStats()
 */
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

/*****************************************************************************
 *                                 协程相关
 ****************************************************************************/
//启用协程，必须添加 croutine.c
#define configUSE_CO_ROUTINES 		0
//协程有效优先级数目
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/*****************************************************************************
 *                               软件定时器相关
 ****************************************************************************/
//启用软件定时
#define configUSE_TIMERS				1
//软件定时的优先级
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
//软件定时队列的个数
#define configTIMER_QUEUE_LENGTH		10
//软件定时器服务/守护任务的堆栈深度
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/*****************************************************************************
 *                               可选函数配置选项
 ****************************************************************************/
/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_xTaskGetSchedulerState  1
#define INCLUDE_eTaskGetState           1
#define INCLUDE_xTimerPendFunctionCall  1

/*****************************************************************************
 *                             中断相关，主要是优先级
 ****************************************************************************/
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		4//__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

//中断最低优先级
/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

//系统可管理的最高优先级
/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/*****************************************************************************
 *                               中断服务函数相关
 ****************************************************************************/
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler//不使用默认的systick中断函数

#endif /* FREERTOS_CONFIG_H */


