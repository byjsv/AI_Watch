#include "stm32f10x.h"
#include "freeRTOS.h"
#include "task.h"
#include "Key.h"

#define STAY_TIME 30		//	消抖时间
#define LATE_TIME 300		//	间隔时间

// 定义按键队列句柄
QueueHandle_t xKeyQueue;


/**
 * @brief 按键初始化
 * 
 * @param 无
 * @return 无
 * @note 选用PB12,13,14,15引脚,	函数包含了按键任务创建和事件队列创建
 * @warning 无
 */
void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 创建按键事件队列，最多存储1个事件
    xKeyQueue = xQueueCreate(1, sizeof(KeyEvent_t));
    
    // 创建按键扫描任务
    xTaskCreate(vKeyScanTask, "KeyScan", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
}

/**
 * @brief 按键任务函数
 * 
 * @param 无
 * @return 无
 * @note 采用任务扫描法依次判断按键是否按下
 * @warning 无
 */
void vKeyScanTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xScanInterval = pdMS_TO_TICKS(STAY_TIME*4);
    KeyEvent_t xKeyEvent = {0};
    
    while (1)
    {
        xKeyEvent.Enter_Pressed = 0;
        xKeyEvent.Up_Pressed = 0;
        xKeyEvent.Down_Pressed = 0;
        
        // 扫描Enter键(PB14)
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(STAY_TIME));
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
            {
                xKeyEvent.Enter_Pressed = 1;
            }
        }
        
        // 扫描Up键(PB15)
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(STAY_TIME));
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
            {
                xKeyEvent.Up_Pressed = 1;
            }
        }
        
        // 扫描Down键(PB13)
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(STAY_TIME));
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
            {
                xKeyEvent.Down_Pressed = 1;
            }
        }
        
        if (xKeyEvent.Enter_Pressed || 
            xKeyEvent.Up_Pressed || xKeyEvent.Down_Pressed)
        {
            xQueueSend(xKeyQueue, &xKeyEvent, 0);
			vTaskDelay(pdMS_TO_TICKS(LATE_TIME));
        }
        
        vTaskDelayUntil(&xLastWakeTime, xScanInterval);
    }
}

/**
 * @brief 读取一个按键事件队列的事件
 * 
 * @param 要存储的事件对象位置,	间隔的时间
 * @return pdTRUE | pdFALSE
* @warning 返回数据的位置为参数1
 */
BaseType_t Key_GetEvent(KeyEvent_t *pxKeyEvent, TickType_t xTicksToWait)
{
    return xQueueReceive(xKeyQueue, pxKeyEvent, xTicksToWait);
}
