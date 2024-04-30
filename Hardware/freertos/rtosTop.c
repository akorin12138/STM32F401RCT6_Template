#include "sys.h"

#define TASK1_TASK_PRIO                        2
#define TASK1_STK_SIZE                        120
void task1_task(void * p);
TaskHandle_t Task1Task_Handler; 

#define TASK2_TASK_PRIO                        3
#define TASK2_STK_SIZE                        120
void task2_task(void * p);
TaskHandle_t Task2Task_Handler; 

#define LED_TASK_PRIO													4
#define LED_STK_SIZE													120
void led_blink(void *p);
TaskHandle_t ledTask_Handler;


static TaskHandle_t xTask_creat;

/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
static void creat_task(void *p)
{
    user_main_info("%s", __FUNCTION__);
    int cnt = 0;

	  xTaskCreate(
			(TaskFunction_t ) task1_task,
      (char*        ) "task1",
      (uint16_t     ) TASK1_STK_SIZE,
      (void *       ) NULL,
      (UBaseType_t  ) TASK1_TASK_PRIO,
      (TaskHandle_t*) &Task1Task_Handler);
	  xTaskCreate(
			(TaskFunction_t ) task2_task,
      (char*        ) "task2",
      (uint16_t     ) TASK2_STK_SIZE,
      (void *       ) NULL,
      (UBaseType_t  ) TASK2_TASK_PRIO,
      (TaskHandle_t*) &Task2Task_Handler);
		xTaskCreate(
			(TaskFunction_t ) led_blink,
			(char* 					)	"ledTask",
			(uint16_t				)	LED_STK_SIZE,
			(void * 				)	NULL,
			(UBaseType_t		)	LED_TASK_PRIO,
			(TaskHandle_t*	)	&ledTask_Handler);
    taskENTER_CRITICAL();
					// main() enter here;
    taskEXIT_CRITICAL();

#if 1
    while(1){
        user_main_info("this is creat task:idle-%d", cnt++);
        vTaskDelay(1000);
        if (cnt >= 2){
            break;
        }
    }
#endif

    user_main_info("delete creat task");

    vTaskDelete(xTask_creat);
}
/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
int rtos_init(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    BaseType_t xReturn = pdPASS;
    user_main_info("Freertos v10.3.1 start ");
    xReturn = xTaskCreate(  (TaskFunction_t )creat_task,
                            (const char *   )"creat_task",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&xTask_creat);

    if (pdPASS != xReturn){
        return -1;
    }
    vTaskStartScheduler();
    return xReturn;
}

void task1_task(void * p){
	char task1_num=0;
	while(1){
		user_main_debug("task1 %d",task1_num);
		task1_num++;
		vTaskDelay(1000);
	}
}

void task2_task(void * p){
	char task2_num=0;
	while(1){
		user_main_debug("task2 %d",task2_num);
		task2_num++;
		vTaskDelay(500);
	}
}
void led_blink(void * p){
	while(1){
		ledon;
		vTaskDelay(500);
		ledoff;
		vTaskDelay(500);
	}
}