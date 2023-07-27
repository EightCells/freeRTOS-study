#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 * ���������������վ�鿴��Ӧѡ��Ĺٷ����ͣ����ļ���ע��ֻ���ο�
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
//#include "gd32f30x.h"
/* ����ǲȹ��Ŀӣ���Ϊ���ҲҪ�õ�FreeRTOSConfig.h�ļ���������Щ�ؼ���
 * �� enum �ͻᱨ bad instruction �Ĵ���������û���ֱ�Ӱ��� 
 * SystemCoreClock �����ĺ��ֱֵ��ճ�������ã����������������Ͳ�Ҫ�ٰ���
 *  gd32f30x.h �ˡ�*/
/* Ensure stdint is only used by the compiler, and not the assembler. */
//����ط�__ICCARM__��ʾ��IAR�ı�����������Keil��GCCҪ�ĳ�__CC_ARM��__GNUC__
#if defined __ICCARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

//assert����
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	

/*****************************************************************************
 *                                ����������
 ****************************************************************************/
//����������ռʽ 1 Э��ʽ 0
#define configUSE_PREEMPTION			1

//1 ʹ��ʱ��Ƭ����(Ĭ����ʹ�ܵ�)
#define configUSE_TIME_SLICING          1

//�Ƿ�ʹ��Ӳ������ǰ��0�ķ�ʽѡ����һ����ִ������
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* ��1��ʹ�ܵ͹���tickless ģʽ����0������ϵͳ���ģ�tick���ж�һֱ���� */
#define configUSE_TICKLESS_IDLE         0

//д��ʵ��CPU�ں�ʱ��Ƶ��
#define configCPU_CLOCK_HZ				((uint32_t)(120000000))//( SystemCoreClock )

//1s�жϵĴ���
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )

//���õ�������ȼ�
#define configMAX_PRIORITIES			( 32 )

//���������ջ��С
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )

//����������󳤶�
#define configMAX_TASK_NAME_LEN			( 16 )

//ϵͳ���ļ������������������ͣ�1 16λ�޷���������0 32λ�޷�������
#define configUSE_16_BIT_TICKS			0

//�����������CPUʹ��Ȩ������ͬ�����񣨽�������������������ȼ����ڿ�������
#define configIDLE_SHOULD_YIELD			1

//���ö���
#define configUSE_QUEUE_SETS            1

//��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_TASK_NOTIFICATIONS    1

//�����ź���
#define configUSE_MUTEXES               1

//����ע����ź����ĸ���
#define configQUEUE_REGISTRY_SIZE       10

//ʹ�õݹ黥���ź���
#define configUSE_RECURSIVE_MUTEXES     1

//��ע�����Ϣ���еĸ���
#define configUSE_APPLICATION_TASK_TAG  0

//ʹ�ü����ź���
#define configUSE_COUNTING_SEMAPHORES   1

/*****************************************************************************
 *                                �ڴ��������
 ****************************************************************************/
//֧�ֶ�̬�ڴ�����
#define configSUPPORT_DYNAMIC_ALLOCATION 1
//֧�־�̬�ڴ�
#define configSUPPORT_STATIC_ALLOCATION 0
//�ܶ�ջ��С
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 36 * 1024 ) )

/*****************************************************************************
 *                                ���Ӻ������
 ****************************************************************************/
//���й��ӣ���������ִ�е�Ӧ�ó�������void vApplicationIdleHook( void );
#define configUSE_IDLE_HOOK				0
//ʱ��Ƭ���Ӻ��� void vApplicationTickHook( void );
#define configUSE_TICK_HOOK				0
//mallocʧ��ʱ������NULL�����õĹ��Ӻ��� void vApplicationMallocFailedHook( void );
#define configUSE_MALLOC_FAILED_HOOK    0
//��ջ������ ����0ʱ���ã��������û��ṩ��ջ������Ӻ���
#define configCHECK_FOR_STACK_OVERFLOW  0

/*****************************************************************************
 *                         ����ʱ�������״̬�ռ����
 ****************************************************************************/
//��������ʱ��ͳ�ƹ���
#define configGENERATE_RUN_TIME_STATS   0
//���ÿ��ӻ����ٵ���
#define configUSE_TRACE_FACILITY        0
/* ���configUSE_TRACE_FACILITY ͬʱΪ 1 ʱ��������� 3 ������
 * prvWriteNameToBuffer()
 * vTaskList(),
 * vTaskGetRunTimeStats()
 */
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

/*****************************************************************************
 *                                 Э�����
 ****************************************************************************/
//����Э�̣�������� croutine.c
#define configUSE_CO_ROUTINES 		0
//Э����Ч���ȼ���Ŀ
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/*****************************************************************************
 *                               �����ʱ�����
 ****************************************************************************/
//���������ʱ
#define configUSE_TIMERS				1
//�����ʱ�����ȼ�
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
//�����ʱ���еĸ���
#define configTIMER_QUEUE_LENGTH		10
//�����ʱ������/�ػ�����Ķ�ջ���
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/*****************************************************************************
 *                               ��ѡ��������ѡ��
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
 *                             �ж���أ���Ҫ�����ȼ�
 ****************************************************************************/
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		4//__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

//�ж�������ȼ�
/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

//ϵͳ�ɹ����������ȼ�
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
 *                               �жϷ��������
 ****************************************************************************/
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler//��ʹ��Ĭ�ϵ�systick�жϺ���

#endif /* FREERTOS_CONFIG_H */


